#include "tb.h"
#include "Arduino.h"
#include <ShiftRegister74HC595.h>

// This file controls the pins to control the AP and camera

// Shift register
#define  SHCP 14 // Shift register clock
#define  STCP 12 // Register clock (latch)
#define  DS 3   // Serial data

ShiftRegister74HC595<1> shiftRegister(DS, SHCP, STCP);

// Pins on the shift register
#define AP_PIN 0
#define USB_PIN 1
#define USB2_PIN 2


void setup_pins() {
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(DS, OUTPUT);
}

void update_on_off() {
    uint8_t shiftRegisterPins[] = {B00000000};

    // Get attributes

    // Convert to binary

    // Set AP pin
    shiftRegisterPins[AP_PIN] = 0;
    // ...

    // Set the shift register
    shiftRegister.setAll(shiftRegisterPins);
}