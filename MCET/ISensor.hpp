#pragma once
#include <Arduino.h>
#include <string.h>
#define TEMP_UNIT false //change to true if you want to use celcius


class ISensor {   //boilerplate sensor code so I can slam them in an array easily
public:
    virtual ~ISensor() = default;

    virtual const char* name() const = 0;
    virtual String toString() = 0;
};