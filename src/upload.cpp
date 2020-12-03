#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "upload_creds.h"

// Initialize the client library
WiFiClientSecure client;

// Post makes a post to thingsboard with the provided path and body.
int Post(String path, String body) {
    if (!client.connect(UPLOAD_TCP_SERVER, UPLOAD_TCP_PORT)) {
        Serial.println("failed to connect");
        return -1;
    }
    client.print("POST ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.println("Connection: close");
    client.println("User-Agent: device");
    client.println("Content-Type: application/json");
    client.print("Host: ");
    client.println(UPLOAD_TCP_SERVER);
    client.print("Content-Length: ");
    client.print(body.length());
    client.println();
    client.println();
    client.print(body.c_str());
    client.println();
    client.flush();
    client.stop();

    // TODO: return response

    return 0;
}

// SendAttributes sends thingsboard attributes
int SendAttributes(String attributes) {
    return Post("/api/v1/" ACCESS_TOKEN "/attributes", attributes);
}

// SendTelemetry Sends thingsboard telemetry data
int SendTelemetry(String data) {
    return Post("/api/v1/" ACCESS_TOKEN "/telemetry", data);
}
