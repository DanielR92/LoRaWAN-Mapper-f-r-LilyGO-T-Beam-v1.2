#include "LoRaWANManager.h"
#include "StorageManager.h"
#include "config.h"


void LoRaWANManager::begin() {
    // init radio module
    int16_t state = mod.begin();
    if (state != RADIOLIB_ERR_NONE) {
        Serial.print("[LoRa] module.begin() failed: "); Serial.println(state);
    }
    // configure node; region defaults to EU/868 in many examples - set if needed
}


int LoRaWANManager::join() {
    Serial.println("[LoRaWAN] begin OTAA (will try restore if saved)");
    LoRaWANJoinEvent_t joinEvent;
    // try to restore from saved EEPROM session first
    const uint8_t *bufSession=nullptr, *bufNonces=nullptr;
    size_t lenSession=0, lenNonces=0;
    if (StorageManager::loadSession(bufSession, lenSession, bufNonces, lenNonces)) {
        Serial.println("[LoRaWAN] Found saved session - restoring into node buffers");
        // RadioLib provides setBufferSession / setBufferNonces
        node.setBufferSession(bufSession, lenSession);
        node.setBufferNonces(bufNonces, lenNonces);
    }


    int16_t st = node.activateOTAA((uint8_t*)JOIN_EUI, (uint8_t*)DEV_EUI, (uint8_t*)APP_KEY, &joinEvent);
    // activateOTAA tries to restore session; if restore ok it returns RADIOLIB_ERR_NONE with LORAWAN_NEW_SESSION maybe
    if (st == RADIOLIB_ERR_NONE) {
        Serial.println("[LoRaWAN] OTAA activate succeeded");
        joined = true;
        // after join, persist buffers
        persistSessionIfAvailable();
    } else {
        Serial.print("[LoRaWAN] OTAA failed: "); Serial.println(st);
    }
    return st;
}


int LoRaWANManager::sendUplink(const uint8_t* data, size_t len, uint8_t fport) {
    if (!joined) return -1;
    LoRaWANTxParams txParams;
    txParams.port = fport;
    int16_t st = node.transmit(data, len, &txParams);
    // after TX, RadioLib updates internal buffers; persist them
    persistSessionIfAvailable();
    return st;
}


void LoRaWANManager::persistSessionIfAvailable() {
    // get session + nonces from node (if implemented)
    size_t sessionLen=0, noncesLen=0;
    const uint8_t *sessionBuf = node.getBufferSession(&sessionLen);
    const uint8_t *noncesBuf = node.getBufferNonces(&noncesLen);
    if (sessionBuf && sessionLen>0 && noncesBuf && noncesLen>0) {
        StorageManager::saveSession(sessionBuf, sessionLen, noncesBuf, noncesLen);
        Serial.println("[LoRaWAN] Session persisted to EEPROM");
    }
}