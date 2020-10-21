#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "tb_creds.h"

WiFiClientSecure client;

void send_attributes(char* payload) {
    HTTPClient http;

    // Pull attributes
    client.connect(THINGSBOARD_SERVER, 443);
    http.begin(client, THINGSBOARD_SERVER);
    http.GET();
    String out = http.getString();
    Serial.println(out);
}