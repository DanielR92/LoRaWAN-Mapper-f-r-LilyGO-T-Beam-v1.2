#pragma once
#include <SSD1306Wire.h>
#include <Arduino.h>
#include "config.h"

class DisplayManager {
    public:
    void begin();
    void renderStatus(bool joined, float lat, float lon, int sats, float hdop, int batPct);
    private:
        SSD1306Wire display{OLED_ADDR, OLED_SDA, OLED_SCL};
};