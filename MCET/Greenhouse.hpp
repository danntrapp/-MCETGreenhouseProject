#pragma once
#include "Thermistor.hpp"
#include "Photoresistor.hpp"
#include "MotionSens.hpp"
#include "DHT11.hpp"
#include "ISensor.hpp"
namespace GreenhouseConsts {
    const int photoResPin = A0;
    const int thermPin = A1;

    const int dhtPin = 49;
    const int motionSensPin = 40;

    const float referenceRes = 10000.0;
    const float b = 3926.07;
}
class Greenhouse {
  public:

  Greenhouse() : m_photoRes(GreenhouseConsts::photoResPin, GreenhouseConsts::referenceRes),
                 m_therm(GreenhouseConsts::thermPin, GreenhouseConsts::referenceRes, GreenhouseConsts::b),
                 m_dht(GreenhouseConsts::dhtPin),
                 m_motionSens(GreenhouseConsts::motionSensPin) 
  {
    m_sensors[0] = &m_photoRes;
    m_sensors[1] = &m_therm;
    m_sensors[2] = &m_dht;
    m_sensors[3] = &m_motionSens;
  }

  void begin() {
    Serial.begin(115200);
    m_dht.begin();
    m_motionSens.begin();
  }

  ISensor* getSens(int index) { return m_sensors[index]; }

  int numSensors() { return sizeof(m_sensors) / sizeof(m_sensors[0]); 



  private:
  Photoresistor m_photoRes;
  Thermistor m_therm;
  DHT11 m_dht;
  MotionSens m_motionSens;
  ISensor* m_sensors[4];
};