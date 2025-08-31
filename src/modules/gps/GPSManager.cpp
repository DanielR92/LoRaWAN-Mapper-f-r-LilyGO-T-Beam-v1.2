#include "GPSManager.h"
#include "config.h"
#include <HardwareSerial.h>


static HardwareSerial GPSSerial(1);


void GPSManager::begin() {
    GPSSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_SERIAL_RX, GPS_SERIAL_TX);
}


void GPSManager::update() {
    while (GPSSerial.available()) {
        gps.encode((char)GPSSerial.read());
    }
}


bool GPSManager::hasFix() const { return gps.location.isValid(); }
double GPSManager::lat() const { return gps.location.isValid() ? gps.location.lat() : 0.0; }
double GPSManager::lon() const { return gps.location.isValid() ? gps.location.lng() : 0.0; }
double GPSManager::alt() const { return gps.altitude.isValid() ? gps.altitude.meters() : 0.0; }
int GPSManager::sats() const { return gps.satellites.isValid() ? gps.satellites.value() : 0; }
float GPSManager::hdop() const { return gps.hdop.isValid() ? (gps.hdop.hdop()): 99.9; }