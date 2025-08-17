#pragma once
#include <Arduino.h>
#include <TinyGPS++.h>

class GpsModule {
public:
    GpsModule(HardwareSerial &serial, uint32_t baud = 9600);

    void begin();  
    void startTask(const char* name, uint32_t stack, UBaseType_t prio, BaseType_t core);

    // Getter für aktuelle Werte
    double latitude();
    double longitude();
    double altitude();
    double speed();
    uint32_t satellites();
    double hdop();
    bool locationValid();
    bool timeValid();

private:
    static void taskLoop(void* pvParameters);

    HardwareSerial &gpsSerial;
    uint32_t baudRate;
    TinyGPSPlus gps;
};
