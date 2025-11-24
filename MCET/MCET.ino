#include "Greenhouse.hpp"
#include "ScreenModule.hpp"
#include "RotaryEncoder.hpp"

//73.4 F 10750.51 ohm
//88 f 6634.15 
const uint8_t swPin = 11;
const uint8_t clkPin = 13;
const uint8_t dtPin = 12;

const uint8_t rsPin = 8;
const uint8_t ePin = 9;
const uint8_t dPins[] = {4, 5, 6, 7};
int lastIndex = -1;
unsigned long lastValueUpdate = 0;

Greenhouse gh = Greenhouse::Greenhouse();
RotaryEncoder m_encoder = RotaryEncoder(dtPin, swPin, clkPin, gh.numSensors());
ScreenModule sm = ScreenModule::ScreenModule(rsPin, ePin, dPins, gh);
void setup() {
  Serial.begin(9600);
  sm.begin();
  gh.begin();
  m_encoder.begin();
}
void loop() {
    gh.updateControlLogic();
    m_encoder.updateRot();
    int index = m_encoder.cnt();

    // Redraw FULL screen when moving the encoder
    if (index != lastIndex) {
        sm.drawStaticPart(index);          // sensor name, clear screen, etc.
        lastIndex = index;
    }

    // Update only the sensor value every 200 ms (no flicker)
    if (millis() - lastValueUpdate > 200) {
        sm.updateSensorValue(index);
        lastValueUpdate = millis();
    }
}
