#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

// #include "control.h"
#include "temp.h"
#include "wifi.h"
#include "control.h"


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD 115200

extern unsigned long lastSentTemp;

void setup() {
    setup_pins();

    // initialize serial for debugging
    Serial.begin(SERIAL_DEBUG_BAUD);
    
    ConnectToWifi();

    dht_init();

    lastSentTemp = 0;
}

void loop() {
    // Make sure wifi is connected
    reconnect();

    // Submit temp data
    submitData();

    // Update if anything is on or off
    update_on_off();

    // Sleep
    delay(5000);
}