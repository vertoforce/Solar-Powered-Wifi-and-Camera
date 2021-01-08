#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

// #include "control.h"
#include "control.h"
#include "sign_creds.h"
#include "temp.h"
#include "wifi.h"
#include "update.h"
#include "upload.h"

// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD 115200

CustomUpdater updator;

void setup() {

    // Init devices
    SetupSRPins();
    DHTInit();
    pinMode(A0, INPUT);

    // Init serial
    Serial.begin(SERIAL_DEBUG_BAUD);

    // Init wifi
    ConnectToWifi();
}

void SubmitBatteryData() {
    Serial.print("battery value=");
    Serial.print(analogRead(A0));
    Serial.print("\n");
    char payload[50];
    sprintf(payload, "{\"battery_level\":%d}", analogRead(A0));
    SendTelemetry(payload);
}

void loop() {
    // Make sure wifi is connected
    reconnect();

    // Submit data
    SubmitBatteryData();
    SubmitTempData();

    // Update if anything is on or off
    UpdateOnOff();


    // updator.CheckForUpdate();

    // Deep sleep for 5 seconds
    ESP.deepSleep(1000*1000*5);
}