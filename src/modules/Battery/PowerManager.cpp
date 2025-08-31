#include "PowerManager.h"
#include <XPowersLib.h>


static XPowersLibInterface pmu;


void PowerManager::begin() {
    Wire.begin();
    pmu.begin();
}


int PowerManager::batteryPercent() {
    float v = pmu.getBatteryVoltage();
    // simple mapping - refine as you like
    int pct = (int)((v - 3.3) / (4.2 - 3.3) * 100.0);
    pct = constrain(pct, 0, 100);
    return pct;
}