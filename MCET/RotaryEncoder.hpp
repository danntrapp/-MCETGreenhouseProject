#include "CounterHelper.hpp"
#include <Arduino.h>

class RotaryEncoder {
public:
    RotaryEncoder(uint8_t dt, uint8_t sw, uint8_t clk, uint8_t maxCount)
        : m_dtPin(dt), m_swPin(sw), m_clkPin(clk), m_counter(maxCount) {}

    void begin() {
        pinMode(m_dtPin, INPUT);
        pinMode(m_clkPin, INPUT);
        pinMode(m_swPin, INPUT_PULLUP);

        prevState = digitalRead(m_clkPin);
    }

    bool clickPressed() {
        // Button is pressed when LOW (since INPUT_PULLUP)
        if (!digitalRead(m_swPin) && debounce(m_swPin)) {
            return true;
        }
        return false;
    }

    void updateRot() {
        int swState = digitalRead(m_swPin);
        if (swState == LOW) {
            m_counter.reset();
        }

        currentState = digitalRead(m_clkPin);

        // Detect rising edge on CLK
        if ((prevState == LOW) && (currentState == HIGH)) {
            if (digitalRead(m_dtPin) == HIGH) {
                m_counter.decrement();  // Counter-clockwise
            } else {
                m_counter.increment();  // Clockwise
            }
        }

        prevState = currentState;
    }

    int cnt() const {
        return static_cast<int>(m_counter.value());
    }

private:
    bool debounce(uint8_t pin) {
        delay(150);
        return !digitalRead(pin);
    }

    CounterHelper<uint8_t> m_counter;
    int prevState = LOW;
    int currentState = LOW;
    const uint8_t m_dtPin;
    const uint8_t m_swPin;
    const uint8_t m_clkPin;
};
