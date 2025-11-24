#pragma once
#include "Thermistor.hpp"
#include "Photoresistor.hpp"
#include "MotionSens.hpp"
#include "SoilSensor.hpp"
#include "DHT11.hpp"
#include "ISensor.hpp"
namespace GreenhouseConsts {
    const int photoResPin = A0;
    const int thermPin = A1;
    const int soilPin = A2;

    const int dhtPin = 49;
    const int motionSensPin = 40;
    const int fanPin = 2;

    const float photoReferenceRes = 2000.0;
    const float thermReferenceRes = 10000.0;
    const float b = 4138.07;

    const float MIN_TEMP_C = 10.0f;   // safe minimum for plants
    const float MAX_TEMP_C = 35.0f;   // upper temperature limit
    const float MAX_HUMIDITY = 85.0f; // humidity threshold for max fan speed
    const float MIN_HUMIDITY = 40.0f; // humidity threshold for fan off
}
class Greenhouse {
  public:

  Greenhouse() : m_photoRes(GreenhouseConsts::photoResPin, GreenhouseConsts::photoReferenceRes),
                 m_therm(GreenhouseConsts::thermPin, GreenhouseConsts::thermReferenceRes, GreenhouseConsts::b),
                 m_dht(GreenhouseConsts::dhtPin),
                 m_motionSens(GreenhouseConsts::motionSensPin),
                 m_soil(GreenhouseConsts::soilPin, 600, 300)
  {
    m_sensors[0] = &m_photoRes;
    m_sensors[1] = &m_therm;
    m_sensors[2] = &m_soil;
    m_sensors[3] = &m_dht;
    m_sensors[4] = &m_motionSens;
  }

  void begin() {
    pinMode(GreenhouseConsts::fanPin, OUTPUT);
    m_dht.begin();
    m_soil.begin();
    m_motionSens.begin();
  }

  void printShit() {
    for(ISensor* i : m_sensors) {
      Serial.println(i->name());
      Serial.println(i->toString());
    }
    delay(100);
  }



  void printCSVHeader() {
    Serial.print("timestamp_ms,");
    for (int i = 0; i < numSensors(); i++) {
        Serial.print(m_sensors[i]->name());
        if (i < numSensors() - 1) Serial.print(",");
    }
    Serial.println();
}

void logToSerialCSV() {
    unsigned long ts = millis();

    Serial.print(ts);
    Serial.print(",");

    for (int i = 0; i < numSensors(); i++) {
        String s = m_sensors[i]->toString();
        s.replace(",", ";");
        Serial.print(s);
        if (i < numSensors() - 1) Serial.print(",");
    }

    Serial.println();
}


  ISensor* getSens(int index) { return m_sensors[index]; }

  int numSensors() { return sizeof(m_sensors) / sizeof(m_sensors[0]);  }


  void updateControlLogic() {
    m_soil.update();
    controlFan();
  }


  private:

    void controlFan() {
        float H = m_dht.humidityFloat();
        if (!isfinite(H)) return;

        float hum = constrain(H,
                              GreenhouseConsts::MIN_HUMIDITY,
                              GreenhouseConsts::MAX_HUMIDITY);

        int pwm = map(hum,
                      GreenhouseConsts::MIN_HUMIDITY,
                      GreenhouseConsts::MAX_HUMIDITY,
                      0, 255);

        analogWrite(GreenhouseConsts::fanPin, pwm);
    }
  Photoresistor m_photoRes;
  Thermistor m_therm;
  DHT11 m_dht;
  MotionSens m_motionSens;
  SoilSensor m_soil;
  ISensor* m_sensors[5];
};