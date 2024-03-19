#include <Arduino.h>
#include <ESP8266WiFi.h>


#include "eePromTools.h"
#include "configurationHotspot.h"
#include "httpServer.h"
#include "clock.h"
#include "temperatureSensor.h"

String ssid;
String wpa;

String hotterPeriodStart;
String hotterPeriodEnd;
float temperatureHotter;
float temperatureNormal;

ConfigurationHotspot configurationHotspot;
HttpServer httpServer;
Clock timeClock;
TemperatureSensor temperatureSensor;

float currentTemperature;

void setup()
{
  ssid = eepromRead(SSID_START, WPA_START);
  wpa = eepromRead(WPA_START, TEMPERATURE_HOTTER_START);
  temperatureHotter = eepromRead(TEMPERATURE_HOTTER_START, TEMPERATURE_NORMAL_START).toFloat();
  temperatureNormal = eepromRead(TEMPERATURE_NORMAL_START, HOTTER_PERIOD_START_START).toFloat();
  hotterPeriodStart = eepromRead(HOTTER_PERIOD_START_START, HOTTER_PERIOD_END_START);
  hotterPeriodEnd = eepromRead(HOTTER_PERIOD_END_START, HOTTER_PERIOD_END_END);

  WiFi.begin(ssid.c_str(), wpa.c_str());
  httpServer.setup();
}

void loop()
{
  httpServer.tasks();
  configurationHotspot.tasks();
  timeClock.tasks();

  currentTemperature = temperatureSensor.getTemperature();
}
