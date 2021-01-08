#include <ArduinoJson.h>

String SendAttributes(String attributes);
String SendTelemetry(String data);
StaticJsonDocument<400> GetAttributes(char* clientKeys, char* sharedKeys);