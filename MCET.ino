#pragma once
#include "Thermistor.hpp"
#include "Photoresistor.hpp"
#include "DHT11.hpp"
const int photoResPin = A0;
const int dhtPin = 49;
const float referenceRes = 10000.0;
const float b = 3926.07;
// auto thermistor = Thermistor::Thermistor(A0, referenceRes, b);
auto dht = DHT11::DHT11(dhtPin);
 auto state = LOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();

}
void loop() {
  dht.update();

     Serial.print("Temp: ");
        Serial.println(dht.convertCtoF(dht.temperatureFloat()));

        Serial.print("Humidity: ");
        Serial.println(dht.humidityFloat());

        dht.clearNewDataFlag();
  // auto out = thermistor.readResistance();
  // Serial.print("Resistance: ");
  // Serial.println(out);

  // out = thermistor.percentOfMaxRes();
  // Serial.print("% of max");
  // Serial.println(out);
  // float temp = thermistor.readTemperatureF();
  // Serial.print("TempF: ");
  // Serial.println(temp);
  delay(100);

}
