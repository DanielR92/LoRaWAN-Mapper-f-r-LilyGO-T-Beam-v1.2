#include "Oled.h"

void Oled::start(const char* name, uint32_t stack, UBaseType_t priority, BaseType_t core) {
    xTaskCreatePinnedToCore(taskLoop, name, stack, nullptr, priority, nullptr, core);
}

void Oled::taskLoop(void* pvParameters) {
    while (true) {
        Serial.println("[OLED] Updating display...");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
