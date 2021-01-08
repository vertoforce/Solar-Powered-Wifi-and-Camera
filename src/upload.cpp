#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <fetch.h>

#include "upload_creds.h"

// Initialize the client library
WiFiClientSecure client;

// Post makes a post request to the provided path with the provided body.
String Post(String method, String path, String body) {
    if (ESP.getFreeHeap() < 28000) {
        // Do not perform anything, low memory
        return "not enough heap";
    }

    fetch.begin(UPLOAD_TCP_SERVER + path, true);
    // fetch.addHeader("User-Agent", "kilnmon-device");
    if (method == "GET") {
        fetch.GET(path);
    } else if (method == "POST") {
        fetch.addHeader("Content-Type", "application/json");
        fetch.POST(body);
    }

    // Read body
    String returnBody = "";
    while (fetch.busy()) {
        if (fetch.available()) {
           returnBody += fetch.read();
        }
    }
    fetch.clean();

    return returnBody;
}

// SendAttributes sends thingsboard attributes.
// Attributes is the JSON passed to thingsboard to set attributes.
String SendAttributes(String attributes) {
    return Post("POST", "/api/v1/" ACCESS_TOKEN "/attributes", attributes);
}

// SendTelemetry Sends thingsboard telemetry data.
// data is the JSON containing the telementry data.
String SendTelemetry(String data) {
    return Post("POST", "/api/v1/" ACCESS_TOKEN "/telemetry", data);
}

// Get Attributes returns the attributes and their values from the server
StaticJsonDocument<400> GetAttributes(String clientKeys[],
                                      String sharedKeys[]) {
    String clientKeysString = "";
    for (int i = 0; i < sizeof(clientKeys); i++) {
        clientKeysString += clientKeys[i];
        if (i != sizeof(clientKeys)) {
            clientKeysString += ",";
        }
    }

    String sharedKeysString = "";
    for (int i = 0; i < sizeof(clientKeys); i++) {
        clientKeysString += clientKeys[i];
        if (i != sizeof(clientKeys)) {
            clientKeysString += ",";
        }
    }

    String body = Post("GET",
                       "/api/v1/" ACCESS_TOKEN "/attributes?clientKeys=" +
                           clientKeysString + "&sharedKeys=" + sharedKeysString,
                       "");

    StaticJsonDocument<400> doc;
    deserializeJson(doc, body);

    return doc;
}