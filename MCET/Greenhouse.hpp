#pragma once
#include "Thermistor.hpp"
#include "Photoresistor.hpp"
#include "MotionSens.hpp"
#include "DHT11.hpp"
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
  {}

  void begin() {
    Serial.begin(115200);
    m_dht.begin();
    m_motionSens.begin();
  }

  void update() {
      m_dht.update();

     Serial.print("Temp: ");
        Serial.println(m_dht.convertCtoF(m_dht.temperatureFloat()));

        Serial.print("Humidity: ");
        Serial.println(m_dht.humidityFloat());

        m_dht.clearNewDataFlag();
        Serial.println();
        Serial.println();
        auto r = m_motionSens.motionDetected() ? "True" : "False";
        Serial.print("Motion Detected: ");
        Serial.println(r);

        Serial.println();
        Serial.println();

        Serial.print("Therm temp: ");
        Serial.println(static_cast<int>(m_therm.readTemperatureF()));

        Serial.println();
        Serial.println();

        Serial.print("Pct bright: ");
        Serial.println(m_photoRes.percentBright());

        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
  }





  private:
  Photoresistor m_photoRes;
  Thermistor m_therm;
  DHT11 m_dht;
  MotionSens m_motionSens;
};