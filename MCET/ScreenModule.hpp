#pragma once
#include <LiquidCrystal.h>
#include "RotaryEncoder.hpp"
class ScreenModule {
    public:
    ScreenModule(uint8_t rs, uint8_t e, uint8_t dpins[4], uint8_t clk, uint8_t dt, uint8_t sw, uint8_t maxVal) :
        m_lcd(rs, e, dpins[0], dpins[1], dpins[2], dpins[3], m_encoder(dt, sw, clk, maxVal))) {}
    



    private:
    LiquidCrystal m_lcd;
    RotaryEncoder m_encoder;
};