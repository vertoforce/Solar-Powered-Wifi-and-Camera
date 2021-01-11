// This file provides functionality to perform an OTA update
// (updating the code remotely)

#include "update.h"

#include <ESP8266httpUpdate.h>

#include "update_creds.h"

#define UPDATE_CHECK_INTERVAL 5 * 60 * 1000

const String version_string = __TIMESTAMP__;

// For signed binaries
BearSSL::PublicKey signPubKey(PUBLIC_KEY);
BearSSL::HashSHA256 hash;
BearSSL::SigningVerifier sign(&signPubKey);

CustomUpdater::CustomUpdater() {
    lastChecked = 0;

    // Set up our key for signed binaries
    // Update.installSignature(&hash, &sign);
}

void CustomUpdater::CheckForUpdate() {
    Serial.println("Checking for update");
    lastChecked = millis();
    ESPhttpUpdate.rebootOnUpdate(true);
    t_httpUpdate_return ret = ESPhttpUpdate.update(UPDATE_SERVER, version_string);
    switch (ret) {
        case HTTP_UPDATE_FAILED:
            Serial.println("[update] Update failed.");
            Serial.println(ESPhttpUpdate.getLastErrorString());
            return;
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("[update] Update no Update.");
            return;
        case HTTP_UPDATE_OK:
            Serial.println("[update] Update ok.");
            return;
    }
}