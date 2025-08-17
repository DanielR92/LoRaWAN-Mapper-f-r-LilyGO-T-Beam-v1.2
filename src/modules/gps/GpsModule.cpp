#include "GpsModule.h"

GpsModule::GpsModule(HardwareSerial &serial, uint32_t baud) 
: gpsSerial(serial), baudRate(baud) {}

void GpsModule::begin() {
    gpsSerial.begin(baudRate, SERIAL_8N1, 16, 17); 
    // RX=16, TX=17 – anpassen an deine Pins!
}

void GpsModule::startTask(const char* name, uint32_t stack, UBaseType_t prio, BaseType_t core) {
    xTaskCreatePinnedToCore(taskLoop, name, stack, this, prio, nullptr, core);
}

void GpsModule::taskLoop(void* pvParameters) {
    auto *self = static_cast<GpsModule*>(pvParameters);
    for (;;) {
        while (self->gpsSerial.available()) {
            self->gps.encode(self->gpsSerial.read());
        }
        // Debug-Ausgabe
        if (self->gps.location.isUpdated()) {
            Serial.printf("[GPS] Lat: %.6f, Lon: %.6f, Alt: %.2f m, Sats: %d\n",
                          self->gps.location.lat(),
                          self->gps.location.lng(),
                          self->gps.altitude.meters(),
                          self->gps.satellites.value());
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Getter
double GpsModule::latitude()    { return gps.location.lat(); }
double GpsModule::longitude()   { return gps.location.lng(); }
double GpsModule::altitude()    { return gps.altitude.meters(); }
double GpsModule::speed()       { return gps.speed.kmph(); }
uint32_t GpsModule::satellites(){ return gps.satellites.value(); }
double GpsModule::hdop()        { return gps.hdop.hdop(); }
bool GpsModule::locationValid() { return gps.location.isValid(); }
bool GpsModule::timeValid()     { return gps.time.isValid(); }
