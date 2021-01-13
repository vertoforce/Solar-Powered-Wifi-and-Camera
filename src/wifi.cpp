#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "wifi_creds.h"

void reconnect() {
    // Loop until we're reconnected
    int status = WiFi.status();
    if (status != WL_CONNECTED) {
        Serial.print("Now connecting to wifi from my mac: ");
        Serial.print(WiFi.macAddress());
        Serial.print("\n");
        wifi_promiscuous_enable(0);
        wifi_set_opmode(STATION_MODE);
        WiFi.begin(WIFI_AP, WIFI_PASSWORD);
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            if (millis() - startTime > 1000*60) {
                Serial.println("Failed to connect");
                // Give up
                return;
            }
        }
        Serial.print("Connected ");
        Serial.println(WiFi.localIP());
    }
}
