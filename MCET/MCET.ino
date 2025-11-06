#include "Greenhouse.hpp"

auto plantZone = Greenhouse::Greenhouse();
void setup() {
  plantZone.begin();
}
void loop() {
  plantZone.update();

  delay(500);

}
