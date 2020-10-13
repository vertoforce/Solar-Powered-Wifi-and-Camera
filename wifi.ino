#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "wifi_creds.h"

void ConnectToWifi() {
    Serial.print("Now connecting to wifi from my mac: ");
    Serial.print(WiFi.macAddress());
    Serial.print("\n");
    wifi_promiscuous_enable(0);
    wifi_set_opmode(STATION_MODE);
    reconnect();
    return;
}

void reconnect() {
    // Loop until we're reconnected
    int status = WiFi.status();
    if (status != WL_CONNECTED) {
        WiFi.begin(WIFI_AP, WIFI_PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.print("Connected ");
        Serial.println(WiFi.localIP());
    }
}