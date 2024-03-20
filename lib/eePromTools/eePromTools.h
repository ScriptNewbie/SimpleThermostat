#pragma once
#include <Arduino.h>
#include <EEPROM.h>

#define SSID_START 0
#define SSID_END 100
#define WPA_START SSID_END
#define WPA_END 200
#define HYSTERESIS_START WPA_END
#define HYSTERESIS_END HYSTERESIS_START + 4
#define DEFAULT_TEMPERATURE_START HYSTERESIS_END
#define DEFAULT_TEMPERATURE_END DEFAULT_TEMPERATURE_START + 4

#define HEATING_PERIODS_START 1024
#define HEATING_PERIODS_END 2049

String eepromRead(unsigned int startAddress, unsigned int endAddress);
String eepromWrite(unsigned int startAddress, String value);
void clearEeprom();