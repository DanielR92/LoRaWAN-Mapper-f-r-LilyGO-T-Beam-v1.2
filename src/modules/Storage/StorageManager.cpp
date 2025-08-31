#include "StorageManager.h"
#include "config.h"
#include <EEPROM.h>


// Simple layout in EEPROM:
// [magic(4)] [lenSession(2)] [lenNonces(2)] [sessionBytes] [noncesBytes]


static const uint32_t MAGIC = 0x5A5A3C3C;


void StorageManager::begin() {
    EEPROM.begin(EEPROM_SIZE);
}


bool StorageManager::loadSession(const uint8_t* &bufSession, size_t &lenSession, const uint8_t* &bufNonces, size_t &lenNonces) {
    uint32_t magic = 0;
    EEPROM.get(0, magic);

    if (magic != MAGIC) return false;
    uint16_t ls = 0, ln = 0;
    EEPROM.get(4, ls);
    EEPROM.get(6, ln);

    if (ls == 0 || ln == 0) return false;
    static uint8_t sessionBuf[256];
    static uint8_t noncesBuf[64];
    lenSession = min((size_t)ls, sizeof(sessionBuf));
    lenNonces = min((size_t)ln, sizeof(noncesBuf));
    int base = 8;

    for (size_t i=0;i<lenSession;i++) sessionBuf[i] = EEPROM.read(base + i);
    base += lenSession;
    
    for (size_t i=0;i<lenNonces;i++) noncesBuf[i] = EEPROM.read(base + i);
    bufSession = sessionBuf;
    bufNonces = noncesBuf;

    return true;
}


void StorageManager::saveSession(const uint8_t* bufSession, size_t lenSession, const uint8_t* bufNonces, size_t lenNonces) {
    EEPROM.put(0, MAGIC);
    uint16_t ls = (uint16_t)min(lenSession, 65535u);
    uint16_t ln = (uint16_t)min(lenNonces, 65535u);
    EEPROM.put(4, ls);
    EEPROM.put(6, ln);
    int base = 8;

    for (size_t i=0;i<ls;i++) EEPROM.write(base + i, bufSession[i]);
    base += ls;

    for (size_t i=0;i<ln;i++) EEPROM.write(base + i, bufNonces[i]);
    EEPROM.commit();
}


void StorageManager::clear() {
    EEPROM.put(0, (uint32_t)0);
    EEPROM.commit();
}