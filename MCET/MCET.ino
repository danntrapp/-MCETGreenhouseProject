#pragma once
#include "ScreenModule.hpp"
#include "Greenhouse.hpp"


const uint8_t dtPin = 40;
const uint8_t swPin = 38;
const uint8_t clkPin = 42;

const uint8_t rsPin = 1;
const uint8_t ePin = 2;
const uint8_t dPins[] = {4, 5, 6, 7};

auto gh = Greenhouse();
ScreenModule sM(rsPin, ePin, dPins, clkPin, dtPin, swPin, &gh);
void setup() {
  Serial.begin(9600);
  sM.begin();
  gh.begin();
}
void loop() {
   sM.updateDisplay();
}
