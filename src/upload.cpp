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
    if (WiFi.status() != WL_CONNECTED) {
        return "no wifi";
    }

    client.setInsecure();
    if (!client.connect(UPLOAD_TCP_SERVER, UPLOAD_TCP_PORT)) {
        Serial.println("failed to connect");
        return "error";
    }
    client.println(method+" "+path+" HTTP/1.1");
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

    // Find the real body, after the headers
    const char* returnBody = client.readString().c_str();
    char* bodyBreak = strstr(returnBody, "\r\n\r\n");
    client.stop();

    if (bodyBreak != NULL) {
        return bodyBreak+4;
    }

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
// clientKeys and sharedKeys are a comma separated stirng of requested keys.
JsonObject GetAttributes(char *clientKeys, char* sharedKeys) {
    char url[150];
    sprintf(url, "/api/v1/" ACCESS_TOKEN "/attributes?clientKeys=%s&sharedKeys=%s", clientKeys, sharedKeys);
    String body = Post("GET", String(url), "");

    StaticJsonDocument<JSON_OBJECT_SIZE(6)> doc;
    DeserializationError err = deserializeJson(doc, body.c_str());
    if (err != NULL) {
        Serial.println(err.c_str());
        Serial.println("body:");
        Serial.println(body);
    }
    JsonObject object = doc.as<JsonObject>();

    return object;
}