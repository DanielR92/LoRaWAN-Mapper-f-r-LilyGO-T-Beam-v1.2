#include <Arduino.h>
#include "config.h"
#include "modules/oled/DisplayManager.h"
#include "modules/gps/GPSManager.h"
#include "modules/Battery/PowerManager.h"
#include "modules/radio/LoRaWANManager.h"
#include "modules/Storage/StorageManager.h"

DisplayManager display;
GPSManager gps;
PowerManager power;
LoRaWANManager lora;


unsigned long lastSend = 0;


void setup() {
Serial.begin(115200);
delay(200);
Serial.println("Tracker boot");


Wire.begin();
StorageManager::begin();


display.begin();
gps.begin();
power.begin();
lora.begin();


display.renderStatus(false, 0, 0, 0, 99.9, 0);


// try join (will attempt session restore first)
int st = lora.join();
Serial.print("Join result: "); Serial.println(st);
}


void loop() {
  gps.update();
  display.renderStatus(lora.isJoined(), (float)gps.lat(), (float)gps.lon(), gps.sats(), gps.hdop(), power.batteryPercent());


  if (gps.hasFix() && millis() - lastSend > SEND_INTERVAL && lora.isJoined()) {
    int32_t ilat = (int32_t)(gps.lat() * 1e6);
    int32_t ilon = (int32_t)(gps.lon() * 1e6);
    int16_t ialt = (int16_t)(gps.alt());
    uint8_t payload[10];
    memcpy(payload + 0, &ilat, 4);
    memcpy(payload + 4, &ilon, 4);
    memcpy(payload + 8, &ialt, 2);
    int16_t res = lora.sendUplink(payload, 10, 1);
    Serial.print("Uplink result: "); Serial.println(res);
    lastSend = millis();
  }

  delay(200);
}