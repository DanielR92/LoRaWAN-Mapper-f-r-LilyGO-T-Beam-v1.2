#pragma once
#include <Arduino.h>


class PowerManager {
    public:
        void begin();
        int batteryPercent();
};