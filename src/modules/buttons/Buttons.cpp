#include "Buttons.h"

void Buttons::start(const char* name, uint32_t stack, UBaseType_t priority, BaseType_t core) {
    xTaskCreatePinnedToCore(taskLoop, name, stack, nullptr, priority, nullptr, core);
}

void Buttons::taskLoop(void* pvParameters) {
    while (true) {
        Serial.println("[Buttons] Checking buttons...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
