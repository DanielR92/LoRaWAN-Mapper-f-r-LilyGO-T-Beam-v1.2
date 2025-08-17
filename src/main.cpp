#include <Arduino.h>
#include "modules/buttons/Buttons.h"
#include "modules/gps/GpsModule.h"
#include "modules/oled/Oled.h"
#include "modules/radio/LoRaWAN.h"

class MainApp {
    public:
        static void start() {
            // Jeder Task mit eigenem Namen, Stackgröße, Priorität, CPU
            Buttons::start("Buttons", 4096, 1, APP_CPU_NUM);
            Oled::start("OLED", 4096, 1, APP_CPU_NUM);
            LoRaWAN::start("LoRaWAN", 4096, 1, PRO_CPU_NUM);

            // GPS braucht eine Instanz
            gps.begin();
            gps.startTask("GPS", 4096, 1, PRO_CPU_NUM);
        }

        static GpsModule gps; // eine globale Instanz
};

GpsModule MainApp::gps(Serial1, 9600);   // <-- Definition mit Konstruktor

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starte MainApp...");
    MainApp::start();
}

void loop() {
    // optional: auf aktuelle Werte zugreifen
    if (MainApp::gps.locationValid()) {
        Serial.printf("Loop: Lat=%.6f, Lon=%.6f\n",
                      MainApp::gps.latitude(),
                      MainApp::gps.longitude());
    }
    delay(2000);
}
 