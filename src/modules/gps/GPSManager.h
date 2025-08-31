#pragma once
#include <TinyGPSPlus.h>
#include <Arduino.h>


class GPSManager {
    public:
        void begin();
        void update();
        bool hasFix() const;
        double lat() const;
        double lon() const;
        double alt() const;
        int sats() const;
        float hdop() const;
        
    private:
        TinyGPSPlus gps;
};

