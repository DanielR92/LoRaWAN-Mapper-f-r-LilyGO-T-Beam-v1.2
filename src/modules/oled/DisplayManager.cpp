#include "DisplayManager.h"
#include "config.h"


void DisplayManager::begin() {
display.init();
display.clear();
display.setFont(ArialMT_Plain_10);
display.drawString(0,0,"T-Beam Tracker");
display.display();
}


void DisplayManager::renderStatus(bool joined, float lat, float lon, int sats, float hdop, int batPct) {
display.clear();
display.setTextAlignment(TEXT_ALIGN_LEFT);
display.drawString(0, 0, joined ? "JOIN: OK" : "JOIN: ---");
display.drawString(0, 12, "SAT: " + String(sats) + " HDOP:" + String(hdop,1));
display.drawString(0, 24, "LAT: " + String(lat,6));
display.drawString(0, 36, "LON: " + String(lon,6));
display.drawString(0, 50, "BAT: " + String(batPct) + "%");
display.display();
}