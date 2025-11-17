#pragma once
#include "VariableResistor.hpp"
#include <string.h>

class Thermistor : public VariableResistor {
public:
  Thermistor(uint8_t pin, float referenceRes, float beta)
    : VariableResistor(pin, referenceRes), m_beta(beta) {}

  float readTemperatureC() const {
    float R = readResistance();
    if (!isfinite(R)) return NAN;  //if reading infinity, return NOT A NUMBER
    //reference vals
    const float T0 = 298.15f;  // 25°C in Kelvin
    const float R0 = getReferenceRes();
    // 1/T
    float invT = (1.0f / T0) + (1.0f / m_beta) * log(R / R0);
    //find T
    float T = 1.0f / invT;  // Kelvin
    return T - 273.15f;     // Celsius
  }

  float readTemperatureF() const {
    float C = readTemperatureC();
    if (!isfinite(C)) return NAN;
    return (C * 9.0f / 5.0f) + 32.0f;
  }

  String toString() override {
    String unit = TEMP_UNIT ? " Degrees Celsius" : " Degrees Fahrenheit";
    auto val = TEMP_UNIT ? static_cast<int>(readTemperatureC()) : static_cast<int>(readTemperatureF());
    auto ret = static_cast<String>(val) + unit;
    return ret;
  }

  const char* name() const override { return "Thermistor"; }

private:
  float m_beta;  // Beta constant
};