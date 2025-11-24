#pragma once
#include "ISensor.hpp"

class SoilSensor : public ISensor {
public:
    SoilSensor(uint8_t pin, int dryVal, int wetVal, float filt = 0.1f)
        : m_pin(pin), DRY(dryVal), WET(wetVal), alpha(filt) {}

    void begin() {
        analogRead(m_pin);
        filtered = analogRead(m_pin);
    }

    void update() {
        int raw = analogRead(m_pin);
        filtered = alpha * raw + (1.0f - alpha) * filtered;
    }

    float moisture() const {
        float v = constrain(filtered, WET, DRY);
        float pct = 100.0f * (DRY - v) / (DRY - WET);
        return 100 - pct;
    }

    int raw() const { return filtered; }

    // --- ISensor interface ---
    const char* name() const override { return "Soil Moisture"; }

    String toString() override {
        float m = moisture();
        if (!isfinite(m)) return "ERR";
        return String((int)m) + "% Moisture";
    }

private:
    uint8_t m_pin;
    int DRY, WET;
    float alpha;
    float filtered = 0;
};
