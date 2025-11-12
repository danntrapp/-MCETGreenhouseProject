// #include "Greenhouse.hpp"
#include "RotaryEncoder.hpp"

const uint8_t dtPin = 40;
const uint8_t swPin = 38;
const uint8_t clkPin = 42;
RotaryEncoder rotEncoder(dtPin, swPin, clkPin, 10);
void setup() {
  rotEncoder.begin();
  Serial.begin(9600);
}
void loop() {
    rotEncoder.updateRot();  // Read rotary input & update internal counter

    // Optional: reset on click
    if (rotEncoder.clickPressed()) {
        Serial.println("Button pressed — counter reset!");
    }

    // Read current count
    int currentCount = rotEncoder.cnt();

    // Print the count (optional: print only when it changes)
    static int prevCount = -1;
    if (currentCount != prevCount) {
        Serial.print("Count: ");
        Serial.println(currentCount);
        prevCount = currentCount;
    }

    delay(10);  // small delay for stability
}
