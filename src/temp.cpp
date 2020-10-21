#include <DHT.h>
#include "tb.h"
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
    sprintf(payload, "{\"temperature\":%f, \"humidity\":%f}", dht.readTemperature(), dht.readHumidity());
    SendAttributes(payload);
}