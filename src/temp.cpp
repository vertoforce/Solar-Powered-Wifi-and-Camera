#include <DHT.h>
#include "tb.h"
#include "pins.h"

#define DHTTYPE DHT22   

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void dht_init() {
    Serial.println("init DHT");
    dht.begin();
}

float read_temp() {
    return dht.readTemperature();
}

float read_humidity() {
    return dht.readHumidity();
}

// read the temperature and submit it to thingsboard
void submitData() {
    char payload[50];
    sprintf(payload, "{\"temperature\":%f, \"humidity\":%f}", read_temp(), read_humidity());
    send_attributes(payload);
}