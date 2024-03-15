#pragma once
#include <Arduino.h>
#include <EEPROM.h>

#define SSID_START 0
#define WPA_START 100
#define TEMPERATURE_HOTTER_START 200
#define TEMPERATURE_NORMAL_START 204
#define HOTTER_PERIOD_START_START 208
#define HOTTER_PERIOD_END_START 213
#define HOTTER_PERIOD_END_END 218

String eepromRead(unsigned int startAddress, unsigned int endAddress);
String eepromWrite(unsigned int startAddress, String value);
void clearEeprom();