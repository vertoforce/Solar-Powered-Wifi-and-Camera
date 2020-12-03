#include "tb.h"
#include "Arduino.h"
#include <ShiftRegister74HC595.h>
#include "pins.h"

// This file controls the pins to control the AP and camera
ShiftRegister74HC595<1> shiftRegister(DS, SHCP, STCP);

// Pins on the shift register
#define AP_PIN 7
#define USB_PIN 0


void SetupSRPins() {
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(DS, OUTPUT);
}

void UpdateOnOff() {
    // Get attributes

    // Convert to binary

    // Set AP pin
    Serial.write("Setting pins high\n");
    shiftRegister.set(AP_PIN, HIGH);
    shiftRegister.set(USB_PIN, HIGH);
    // ...


    delay(5000);
    Serial.write("Setting pins low\n");
    shiftRegister.set(AP_PIN, LOW);
    shiftRegister.set(USB_PIN,LOW);
}