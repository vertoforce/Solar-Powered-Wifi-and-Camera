#include <DHT.h>
#include "upload.h"
#include "pins.h"

#define DHTTYPE DHT22   

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void DHTInit() {
    Serial.println("init DHT");
    dht.begin();
}

// read the temperature and submit it to thingsboard
void SubmitTempData() {
    char payload[50];
    float temp = dht.readTemperature();
    if (temp == 0) {
        // Try to init again
        dht.begin();
        temp = dht.readTemperature();
    }
    // Do not submit data if temp is empty
    if (temp == 0) {
        return;
    }

    sprintf(payload, "{\"temperature\":%f, \"humidity\":%f}", temp, dht.readHumidity());
    SendTelemetry(payload);
}