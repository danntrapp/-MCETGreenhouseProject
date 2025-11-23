#include "Greenhouse.hpp"
#include "ScreenModule.hpp"

//73.4 F 10750.51 ohm
//88 f 6634.15 
const uint8_t swPin = 38;
const uint8_t clkPin = 42;

const uint8_t rsPin = 1;
const uint8_t ePin = 2;
const uint8_t dPins[] = {4, 5, 6, 7};

Greenhouse gh = Greenhouse::Greenhouse();
ScreenModule sm = ScreenModule::ScreenModule(rsPin, ePin, dPins, clkPin, dtPin, swPin, gh);
void setup() {
  Serial.begin(9600);
  sm.begin();
  gh.begin();
}
void loop() {
  sm.updateDisplay();
}
