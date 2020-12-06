// This file provides functionality to perform an OTA update
// (updating the code remotely)

#include <ESP8266httpUpdate.h>

#include "update_creds.h"
#include "update.h"

#define UPDATE_CHECK_INTERVAL 5 * 60 * 1000

const String version_string = __TIMESTAMP__;

void CustomUpdator::CheckForUpdate() {
    if (millis() - lastChecked > UPDATE_CHECK_INTERVAL) {
        lastChecked = millis();
        t_httpUpdate_return ret = ESPhttpUpdate.update(
            UPDATE_SERVER, UPDATE_PORT, UPDATE_PATH, version_string);

        switch (ret) {
            case HTTP_UPDATE_FAILED:
                Serial.println("[update] Update failed.");
            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("[update] Update no Update.");
            case HTTP_UPDATE_OK:
                Serial.println("[update] Update ok.");
        }
    }
}