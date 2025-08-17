#pragma once

#define APP_NAME "LoRaWAN Mapper for T-Beam"
#define APP_VERSION "1.0.0"

#define T_BEAM_V12  // Define your T-Beam version here

// -----------------------------------------------------------------------------
// GPS
// -----------------------------------------------------------------------------

#define GPS_SERIAL_NUM 1     // SerialX
#define GPS_BAUDRATE 115200  // Make haste!  NMEA is big.. go fast
#define USE_GPS 1

#if defined(T_BEAM_V07)
#define GPS_RX_PIN 12
#define GPS_TX_PIN 15
#elif defined(T_BEAM_V12)  // Or T-Beam v1.1
#define GPS_RX_PIN 34
#define GPS_TX_PIN 12
#define GPS_INT 37  // 30ns accurate timepulse from Neo-6M pin 3
#endif