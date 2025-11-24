#pragma once
#include <LiquidCrystal.h>
#include "Greenhouse.hpp"

class ScreenModule {
    public:
    ScreenModule(uint8_t rs, uint8_t e, uint8_t dpins[4], Greenhouse &greenhouse) :
        m_lcd(rs, e, dpins[0], dpins[1], dpins[2], dpins[3]), m_gh{greenhouse} {}

    void begin() {
        m_lcd.begin(16, 2);
    }

    void updateDisplay(int index) {
        m_lcd.clear();
        ISensor* sens = m_gh.getSens(index);

         m_lcd.println(sens->name());
         m_lcd.setCursor(0, 1);
        m_lcd.println(sens->toString());
        delay(200);
    }
    
    void updateSensorValue(int index) {
    ISensor* sens = m_gh.getSens(index);

    m_lcd.setCursor(0, 1);
    m_lcd.print("                ");   // clear line
    m_lcd.setCursor(0, 1);
    m_lcd.print(sens->toString());     // dynamic value
    }


    void drawStaticPart(int index) {
    ISensor* sens = m_gh.getSens(index);

    m_lcd.clear();
    m_lcd.setCursor(0, 0);
    m_lcd.print(sens->name());
    }




    private:
    
    LiquidCrystal m_lcd;
    Greenhouse &m_gh;
};