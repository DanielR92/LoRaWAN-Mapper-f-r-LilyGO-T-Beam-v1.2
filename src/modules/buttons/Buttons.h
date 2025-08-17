#pragma once
#include <Arduino.h>

class Buttons {
public:
    static void start(const char* name, uint32_t stack, UBaseType_t priority, BaseType_t core);
private:
    static void taskLoop(void* pvParameters);
};
