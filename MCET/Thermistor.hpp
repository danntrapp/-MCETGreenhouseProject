#pragma once
#include "VariableResistor.hpp"
#include <string.h>

class Thermistor : public VariableResistor {
public:
  Thermistor(uint8_t pin, float referenceRes, float beta, float alpha = 0.1f)
    : VariableResistor(pin, referenceRes),
      m_beta(beta),
      m_alpha(alpha),
      m_filteredC(NAN) {}

  float readTemperatureC() {
    float R = this->readResistance();
    if (!isfinite(R)) return NAN;

    const float T0 = 298.15f;  // 25°C in Kelvin
    const float R0 = getReferenceRes();

    float invT = (1.0f / T0) + (1.0f / m_beta) * log(R / R0);
    float T = 1.0f / invT - 273.15f;  // Celsius

    // --- smoothing ---
    if (!isfinite(m_filteredC)) {
      m_filteredC = T; // initialize first value
    } else {
      m_filteredC = m_alpha * T + (1.0f - m_alpha) * m_filteredC;
    }

    return m_filteredC;
  }

  float readTemperatureF() {
    float C = readTemperatureC();
    if (!isfinite(C)) return NAN;
    return (C * 9.0f / 5.0f) + 32.0f;
  }

  String toString() override {
    String unit = TEMP_UNIT ? " Degrees C" : " Degrees F";
    float T = TEMP_UNIT ? readTemperatureC() : readTemperatureF();

    if (!isfinite(T)) return "ERR";

    int val = static_cast<int>(T);
    return static_cast<String>(val) + unit;
  }

  const char* name() const override { return "Thermistor"; }

private:
  float m_beta;
  float m_alpha;      // smoothing factor (0.0–1.0)
  float m_filteredC;  // internal smoothed C
};
