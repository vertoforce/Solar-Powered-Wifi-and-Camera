#include "Arduino.h"
#include <ShiftRegister74HC595.h>
#include "pins.h"
#include "upload.h"

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
    // TODO:
    JsonObject attributes = GetAttributes("", "AP,USB");

    // Convert to binary
    if (attributes["shared"]["AP"] == "HIGH") {
        Serial.println("Setting AP HIGH");
        shiftRegister.set(AP_PIN, HIGH);
    } else {
        Serial.println("Setting AP LOW");
        shiftRegister.set(AP_PIN, LOW);
    }

    if (attributes["shared"]["USB"] == "HIGH") {
        Serial.println("Setting USB HIGH");
        shiftRegister.set(USB_PIN, HIGH);
    } else {
        Serial.println("Setting USB LOW");
        shiftRegister.set(USB_PIN, LOW);
    }
}