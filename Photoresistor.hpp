#pragma once
#include "VariableResistor.hpp"
class PhotoResistor : public VariableResistor {
  public: 
  int percentBright() { //just a wrapper bc i thought it was funny
    return VariableResistor::percentOfMaxRes();
  }
};