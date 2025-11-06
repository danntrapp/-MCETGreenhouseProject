#pragma once
#include "VariableResistor.hpp"

class Thermistor : public VariableResistor {
public:
    Thermistor(uint8_t pin, float referenceRes, float beta)
        : VariableResistor(pin, referenceRes), m_beta(beta) {}

    float readTemperatureC() const {
        float R = readResistance();
        if (!isfinite(R)) return NAN;

        const float T0 = 298.15f;     // 25°C in Kelvin
        const float R0 = getReferenceRes();

        float invT =
            (1.0f / T0) +
            (1.0f / m_beta) * log(R / R0);

        float T = 1.0f / invT;        // Kelvin
        return T - 273.15f;           // Celsius
    }

    float readTemperatureF() const {
        float C = readTemperatureC();
        if (!isfinite(C)) return NAN;
        return (C * 9.0f / 5.0f) + 32.0f;
    }
    private:
    float m_beta;   // Beta constant (e.g., 3950)
};