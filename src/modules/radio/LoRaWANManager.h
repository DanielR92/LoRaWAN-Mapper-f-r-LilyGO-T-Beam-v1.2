#pragma once
#include <Arduino.h>
#include <RadioLib.h>


class LoRaWANManager {
    public:
        void begin();
        int join(); // 0 ok, <0 error
        int sendUplink(const uint8_t* data, size_t len, uint8_t fport = 1);
        bool isJoined() const { return joined; }
    private:
        SX1262 mod = SX1262(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);
        LoRaWANNode node{&mod};
        bool joined = false;
        void persistSessionIfAvailable();
};