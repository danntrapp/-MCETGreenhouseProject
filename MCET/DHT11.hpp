#pragma once
#include <Arduino.h>

class DHT11 {
public:
    static constexpr unsigned long READ_INTERVAL_MS = 1500ul;
    static constexpr unsigned long TIMEOUT_MS       = 50ul;
    static DHT11 *instance;

    DHT11(uint8_t pin)
        : m_pin(pin)
    {
        instance = this;
        memset(m_data, 0, sizeof(m_data));
    }

    void begin() {
        TCCR4A = 0;
        TCCR4B = _BV(CS40);
    }

    void update() {
        const uint32_t now = millis();

        switch (m_state) {
        case WAIT_INTERVAL:
            if ((now - m_lastRead) >= READ_INTERVAL_MS) {
                startReading();
                m_lastRead = now;
                m_state = AWAIT_DATA;
            }
            break;

        case AWAIT_DATA:
            if ((now - m_timeoutStart) >= TIMEOUT_MS) {
                m_lastError = true;
                m_state = WAIT_INTERVAL;
            }
            else if (m_dataReady) {
                m_newSample = true;    
                m_lastError = false;   
                m_dataReady = false;
                m_state = WAIT_INTERVAL;
            }
            break;
        }
    }

    bool hasNewData() const { return m_newSample; }

    void clearNewDataFlag() { m_newSample = false; }

    bool lastReadFailed() const { return m_lastError; }

    // Integers directly from DHT11 bytes
    int temperature() const { return m_data[2]; }
    int temperatureDecimal() const { return m_data[3]; }

    int humidity() const { return m_data[0]; }
    int humidityDecimal() const { return m_data[1]; }

    // Combined float helpers
    float temperatureFloat() const {
        return m_data[2] + (m_data[3] / 10.0f);
    }

    float humidityFloat() const {
        return m_data[0] + (m_data[1] / 10.0f);
    }
    float convertCtoF(float c) { return c * 1.8 + 32; }

    float convertFtoC(float f) { return (f - 32) * 0.55555; }

    // Allow printing of internal raw buffer if needed
    const volatile uint8_t* raw() const { return m_data; }

    void handleISR() {
        static ICState icState = ICP_PP_START;
        static bool firstFall = false;
        static uint16_t tStart = 0;
        static uint8_t mask = 0x80;
        static uint8_t idx  = 0;

        uint16_t tNow = ICR4;

        switch (icState) {
        case ICP_PP_START:
            tStart = tNow;
            TCCR4B |= _BV(ICES4);
            icState = ICP_PP_WIDTH;
            break;

        case ICP_PP_WIDTH: {
            uint16_t dur = tNow - tStart;
            if (dur >= PP_MIN_WIDTH && dur <= PP_MAX_WIDTH) {
                firstFall = false;
                TCCR4B &= ~_BV(ICES4);
                mask = 0x80;
                idx = 0;
                memset((void*)m_data, 0, 5);
                icState = ICP_DATA;
            } else {
                TIMSK4 &= ~_BV(ICIE4);
                icState = ICP_PP_START;
            }
            break;
        }

        case ICP_DATA:
            if (!firstFall) {
                tStart = tNow;
                firstFall = true;
            } else {
                uint16_t dur = tNow - tStart;
                tStart = tNow;

                if (dur >= MIN_ONE_WIDTH && dur <= MAX_ONE_WIDTH)
                    m_data[idx] |= mask;

                mask >>= 1;
                if (mask == 0) {
                    mask = 0x80;
                    idx++;
                    if (idx == 5) {
                        m_dataReady = true;
                        TIMSK4 &= ~_BV(ICIE4);
                        icState = ICP_PP_START;
                    }
                }
            }
            break;
        }
    }

private:
    enum State { WAIT_INTERVAL = 0, AWAIT_DATA };

    volatile uint8_t  m_data[5]{};
    volatile bool     m_dataReady = false;

    bool m_newSample = false;
    bool m_lastError = false;

    uint8_t  m_pin;
    State    m_state = WAIT_INTERVAL;

    uint32_t m_lastRead     = 0;
    uint32_t m_timeoutStart = 0;

    static constexpr uint16_t MIN_ZERO_WIDTH = 1040;
    static constexpr uint16_t MAX_ZERO_WIDTH = 1520;
    static constexpr uint16_t MIN_ONE_WIDTH  = 1600;
    static constexpr uint16_t MAX_ONE_WIDTH  = 2240;
    static constexpr uint16_t PP_MIN_WIDTH   = 1120;
    static constexpr uint16_t PP_MAX_WIDTH   = 1440;

    enum ICState { ICP_PP_START = 0, ICP_PP_WIDTH, ICP_DATA };

    void startReading() {
        pinMode(m_pin, OUTPUT);
        digitalWrite(m_pin, LOW);
        delay(30);

        digitalWrite(m_pin, HIGH);
        pinMode(m_pin, INPUT);

        noInterrupts();
        TCCR4B &= ~_BV(ICES4);
        TIFR4  |= _BV(ICF4);
        TIMSK4 |= _BV(ICIE4);
        interrupts();

        m_timeoutStart = millis();
    }
};

DHT11* DHT11::instance = nullptr;

extern "C" ISR(TIMER4_CAPT_vect)
{
    if (DHT11::instance)
        DHT11::instance->handleISR();
}
