#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

// #include "control.h"
#include "temp.h"
#include "wifi.h"
#include "control.h"
#include "sign_creds.h"


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD 115200

// For signed binaries
BearSSL::PublicKey signPubKey(PUBLIC_KEY);
BearSSL::HashSHA256 hash;
BearSSL::SigningVerifier sign( &signPubKey );

void setup() {
    // Set up our key for signed binaries
    Update.installSignature(&hash, &sign);

    // // Init devices
    // SetupSRPins();
    // DHTInit();

    // Init serial
    Serial.begin(SERIAL_DEBUG_BAUD);

    pinMode(A0, INPUT);
 
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

    Serial.print("read=");
    Serial.print(analogRead(A0));
    Serial.print("\n");

    // Sleep
    delay(500);
}