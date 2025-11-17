#pragma once
#include "VariableResistor.hpp"
class Photoresistor : public VariableResistor {
  public: 
  Photoresistor(uint8_t pin, float referenceRes) : VariableResistor(pin, referenceRes) {
  } 
  int percentBright() { //just a wrapper bc i thought it was funny
    return 100 - VariableResistor::percentOfMaxRes();
  }
  String toString() {
    auto val = static_cast<String>(percentBright());
    auto ret = val + "% Bright";
    return ret;
  }
  const char* name() const override { return "Photoresistor";}
};