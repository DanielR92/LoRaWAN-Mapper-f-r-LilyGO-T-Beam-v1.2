#include "LoRaWAN.h"

void LoRaWAN::start(const char* name, uint32_t stack, UBaseType_t priority, BaseType_t core) {
    xTaskCreatePinnedToCore(taskLoop, name, stack, nullptr, priority, nullptr, core);
}

void LoRaWAN::taskLoop(void* pvParameters) {
    while (true) {
        Serial.println("[LoRaWAN] Sending/Receiving...");
        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}
