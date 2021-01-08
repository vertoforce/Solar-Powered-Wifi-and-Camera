#include <ArduinoJson.h>

String SendAttributes(String attributes);
String SendTelemetry(String data);
JsonObject GetAttributes(char* clientKeys, char* sharedKeys);