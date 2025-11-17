#pragma once
#include <LiquidCrystal.h>
#include "Greenhouse.hpp"
#include "RotaryEncoder.hpp"
class ScreenModule {
    public:
    ScreenModule(uint8_t rs, uint8_t e, uint8_t dpins[4], uint8_t clk, uint8_t dt, uint8_t sw, Greenhouse &greenhouse) :
        m_lcd(rs, e, dpins[0], dpins[1], dpins[2], dpins[3]), m_encoder(dt, sw, clk, m_gh.numSensors()), m_gh(greenhouse) {}

    void begin() {
        m_encoder.begin();
        m_lcd.begin(16, 2);
    }

    void updateDisplay() {
        m_encoder.updateRot();
        int index = m_encoder.cnt();
        ISensor* sens = m_gh.getSens(index);

        m_lcd.setCursor(0, 1);
        m_lcd.print(sens.name());
        m_lcd.setCursor(1, 1);
        m_lcd.print(sens.toString());
    }
    



    private:
    
    LiquidCrystal m_lcd;
    RotaryEncoder m_encoder;
    Greenhouse &m_gh;
};