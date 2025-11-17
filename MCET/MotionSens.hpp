#include "ISensor.hpp"
#include <Arduino.h>

class MotionSens: public ISensor {
  public:
  MotionSens(uint8_t pin) : m_pin(pin) {}

  void begin() {
    pinMode(this->m_pin, INPUT);
  }
  
  bool motionDetected() {
    int input = digitalRead(this->m_pin);
    return (input == HIGH);
  }

  String toString() {
    auto ret = motionDetected() ?
               "Motion has been detected!" : "Nothing detected";
    return ret;
  }
  const char* name() const override { return "Motion Sensor";}

  private: 
  const uint8_t m_pin;
};