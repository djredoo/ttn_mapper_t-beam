#include "display.hpp"
#include "power.hpp"
#include "gps.hpp"
#include "config.hpp"

extern SLEEP_VAR int wakeup_count;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C *u8g2 = nullptr;

void setupDisplay()
{
    setup_gps();
    getGPS();

    Wire.begin(I2C_SDA, I2C_SCL);

    Wire.beginTransmission(0x3C);
    if (Wire.endTransmission() == 0)
    {
        Serial.println("Started OLED");
        u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
        u8g2->begin();
        u8g2->clearBuffer();
        u8g2->setFlipMode(0);
        u8g2->setFontMode(1); // Transparent
        u8g2->setDrawColor(1);
        u8g2->setFontDirection(0);
        u8g2->firstPage();
        do
        {
            u8g2->setFont(u8g2_font_8x13_mr);
            u8g2->setCursor(0,10);
            u8g2->print("Batt:");
            u8g2->setCursor(50,10);
            u8g2->print(PMU->getBattVoltage());
            u8g2->setCursor(0,25);
            u8g2->print("Lat:");
            u8g2->setCursor(50,25);
            u8g2->print(gps.location.lat(), 6);
            u8g2->setCursor(0,40);
            u8g2->print("Long:");
            u8g2->setCursor(50,40);
            u8g2->print(gps.location.lng(), 6);
            Serial.println(gps.location.lat(), 6);
            Serial.println(gps.location.lng(), 6);
            u8g2->setCursor(0,55);
            u8g2->print("Wakecount:");
            u8g2->setCursor(90,55);
            u8g2->print(wakeup_count);
        } while (u8g2->nextPage());
        u8g2->sendBuffer();
        u8g2->setFont(u8g2_font_fur11_tf);
        delay(3000);

    }
}
