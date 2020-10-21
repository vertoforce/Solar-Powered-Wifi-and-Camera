#include "tb.h"
#include "Arduino.h"
#include <ShiftRegister74HC595.h>
#include "pins.h"

// This file controls the pins to control the AP and camera
ShiftRegister74HC595<1> shiftRegister(DS, SHCP, STCP);

// Pins on the shift register
#define AP_PIN 0
#define USB_PIN 1
#define USB2_PIN 2


void SetupSRPins() {
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(DS, OUTPUT);
}

void UpdateOnOff() {
    uint8_t shiftRegisterPins[] = {B00000000};

    // Get attributes

    // Convert to binary

    // Set AP pin
    shiftRegisterPins[AP_PIN] = 0;
    // ...

    // Set the shift register
    shiftRegister.setAll(shiftRegisterPins);
}