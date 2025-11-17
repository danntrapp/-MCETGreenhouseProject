#pragma once
#include "ISensor.hpp"
#include <math.h>
class VariableResistor : public ISensor {
    protected:
    const uint16_t ADCMax = 1023;
    public:

    VariableResistor(uint8_t pin, float referenceRes) : m_pin(pin), m_referenceRes(referenceRes) {}

    float readResistance() {
        float input = analogRead(m_pin);   // read ADC as float
        float ratio = ((float)ADCMax / input) - 1.0f;
        float res = m_referenceRes * ratio;
        return res;
}
    int percentOfMaxRes() {
        double input = analogRead(m_pin);

        int pct = (input * 100) / ADCMax;
        return pct;
    }
    float getReferenceRes() {
        return this->m_referenceRes;
    }

    private: 
    uint8_t m_pin; //input pin
    float m_referenceRes;

    
};