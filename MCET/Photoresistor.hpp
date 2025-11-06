#pragma once
#include "VariableResistor.hpp"
class Photoresistor : public VariableResistor {
  public: 
  Photoresistor(uint8_t pin, float referenceRes) : VariableResistor(pin, referenceRes) {
  } 
  int percentBright() { //just a wrapper bc i thought it was funny
    return VariableResistor::percentOfMaxRes();
  }
};