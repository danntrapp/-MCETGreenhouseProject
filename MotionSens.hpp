#include <Arduino.h>
class MotionSens {

  MotionSens(uint8_t pin) : m_pin(pin) {}

  void begin() {
    pinMode(this->m_pin, INPUT);
  }
  
  bool motionDetected() {
    int input = digitalRead(this->m_pin)
    return (input == HIGH);
  }

  private: 
  const uint8_t m_pin;
}