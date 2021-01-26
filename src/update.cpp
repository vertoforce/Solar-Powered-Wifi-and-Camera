// This file provides functionality to perform an OTA update
// (updating the code remotely)
#include <RTCVars.h>
#include <ESP8266httpUpdate.h>

#include "update.h"
#include "update_creds.h"

#define UPDATE_CHECK_INTERVAL 5 * 60 * 1000


// Variable to keep track of time over deep sleep cycles
long timeOffset;
RTCVars state;

// For signed binaries
BearSSL::PublicKey signPubKey(PUBLIC_KEY);
BearSSL::HashSHA256 hash;
BearSSL::SigningVerifier sign(&signPubKey);

// Create new custom updator, setting up the RTC storage
// so we can remember how much time has passed since the last update
// even over restarts
CustomUpdater::CustomUpdater() {
    // Load time from RTC
    state.registerVar(&timeOffset);
    state.loadFromRTC();

    // Set up our key for signed binaries
    // Update.installSignature(&hash, &sign);
}

// Check if we updated recently, and update if we haven't
void CustomUpdater::CheckForUpdate() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("no wifi to update");
        return;
    }
    if (millis()+((unsigned long) timeOffset) > UPDATE_CHECK_INTERVAL) {
        Serial.println("Checking for update");

        // Reset time offset
        // This has the equivalent effect of storing the last updated time
        // since we will be rebooting
        timeOffset = 0;
        state.saveToRTC();

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
}

// Store the time to be restored over a reset, plus any additional offset (like sleep time for example)
void CustomUpdater::StorePersistentTime(unsigned long additionalOffset) {
    // Store persistent time
    timeOffset += millis();
    Serial.print("current time: ");
    Serial.println(timeOffset);
    timeOffset += additionalOffset;
    state.saveToRTC();
}