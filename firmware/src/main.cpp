#include <Arduino.h>
#include <ESP8266WiFi.h>


#include "eePromTools.h"
#include "heater.h"
#include "configurationHotspot.h"
#include "httpServer.h"

String ssid;
String wpa;

ConfigurationHotspot configurationHotspot;
HttpServer httpServer;
Heater heater;

void setup()
{
  heater.setup();

  ssid = eepromRead(SSID_START, SSID_END);
  wpa = eepromRead(WPA_START, WPA_END);
  WiFi.begin(ssid.c_str(), wpa.c_str());

  httpServer.setup();

  Serial.begin(115200);
  Serial.println("Starting up");
}

void loop()
{
  httpServer.tasks();
  configurationHotspot.tasks();
  heater.tasks();
}
