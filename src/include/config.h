#pragma once


// Pins (T-Beam v1.2 typical) - verify on your board
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C


#define GPS_SERIAL_RX 34
#define GPS_SERIAL_TX 12
#define GPS_BAUD 9600


#define LORA_CS 18
#define LORA_RST 23
#define LORA_BUSY 32
#define LORA_DIO1 33


#define EEPROM_SIZE 512
#define EEPROM_ADDR 0


#define SEND_INTERVAL 30000 // ms


// OTAA keys - replace with your values (hex)
static const uint8_t JOIN_EUI[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
static const uint8_t DEV_EUI[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
static const uint8_t APP_KEY[16] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };