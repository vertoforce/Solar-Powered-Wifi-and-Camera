#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "upload_creds.h"

// Initialize the client library
WiFiClientSecure client;

// Post makes a post to thingsboard with the provided path and body.
String Post(String method, String path, String body) {
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

    // TODO: untested, This will probably return the full body including the headers
    String body = client.readString();
    client.stop();

    return body;
}

// SendAttributes sends thingsboard attributes
String SendAttributes(String attributes) {
    return Post("POST", "/api/v1/" ACCESS_TOKEN "/attributes", attributes);
}

// SendTelemetry Sends thingsboard telemetry data
String SendTelemetry(String data) {
    return Post("POST", "/api/v1/" ACCESS_TOKEN "/telemetry", data);
}

// Get Attributes returns the attributes and their values from the server
StaticJsonDocument<400> GetAttributes(String clientKeys[], String sharedKeys[]) {
    String clientKeysString = "";
    for (int i=0;i<sizeof(clientKeys);i++) {
        clientKeysString += clientKeys[i];
        if (i != sizeof(clientKeys)) {
            clientKeysString += ",";
        }
    }

    String sharedKeysString = "";
    for (int i=0;i<sizeof(clientKeys);i++) {
        clientKeysString += clientKeys[i];
        if (i != sizeof(clientKeys)) {
            clientKeysString += ",";
        }
    }

 
    String body = Post("GET", "/api/v1/" ACCESS_TOKEN "/attributes?clientKeys="+clientKeysString+"&sharedKeys="+sharedKeysString, "");

    StaticJsonDocument<400> doc;
    deserializeJson(doc, body);

    return doc;
}