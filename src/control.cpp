#include "Arduino.h"
#include "ShiftRegister74HC595.h"
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
    // Get attributes, try 3 times
    JsonObject attributes;
    for (int i=0; i<3; i++) {
        attributes = GetAttributes("", "AP,USB");

        if (!attributes.containsKey("shared")) {
            Serial.println("problem getting attributes, trying again");
            // Problem with the JSON, skip this
            continue;
        }
        break;
    }

    // Check if we still failed
    if (!attributes.containsKey("shared")) {
        return;
    }

    // Convert to binary
    if (attributes["shared"]["AP"]) {
        Serial.println("Setting AP HIGH");
        shiftRegister.set(AP_PIN, HIGH);
    } else {
        Serial.println("Setting AP LOW");
        shiftRegister.set(AP_PIN, LOW);
    }

    if (attributes["shared"]["USB"]) {
        Serial.println("Setting USB HIGH");
        shiftRegister.set(USB_PIN, HIGH);
    } else {
        Serial.println("Setting USB LOW");
        shiftRegister.set(USB_PIN, LOW);
    }
}