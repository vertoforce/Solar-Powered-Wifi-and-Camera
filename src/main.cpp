#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

// #include "control.h"
#include "temp.h"
#include "wifi.h"
#include "control.h"


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD 115200

void setup() {
    // Init devices
    SetupSRPins();
    DHTInit();

    // Init serial
    Serial.begin(SERIAL_DEBUG_BAUD);
 
    // Init wifi
    ConnectToWifi();
}

void loop() {
    // Make sure wifi is connected
    reconnect();

    // Submit temp data
    SubmitTempData();

    // Update if anything is on or off
    UpdateOnOff();

    // Sleep
    delay(5000);
}