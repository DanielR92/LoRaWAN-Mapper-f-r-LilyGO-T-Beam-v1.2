#pragma once
#include <Arduino.h>


class StorageManager {
public:
static void begin();
// save/restore raw radiolib session buffers
static bool loadSession(const uint8_t* &bufSession, size_t &lenSession, const uint8_t* &bufNonces, size_t &lenNonces);
static void saveSession(const uint8_t* bufSession, size_t lenSession, const uint8_t* bufNonces, size_t lenNonces);
static void clear();
};

