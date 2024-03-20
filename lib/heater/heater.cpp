#include "heater.h"
#include "eePromTools.h"

void Heater::setup()
{
    temperatureHotter = eepromRead(TEMPERATURE_HOTTER_START, TEMPERATURE_NORMAL_START).toFloat();
    temperatureNormal = eepromRead(TEMPERATURE_NORMAL_START, HOTTER_PERIOD_START_START).toFloat();
    hotterPeriodStart = eepromRead(HOTTER_PERIOD_START_START, HOTTER_PERIOD_END_START);
    hotterPeriodEnd = eepromRead(HOTTER_PERIOD_END_START, HYSTERESIS_START);
    hysteresis = eepromRead(HYSTERESIS_START, HYSTERESIS_END).toFloat();
}

void Heater::tasks()
{
    temperatureSensor.tasks();
    timeClock.tasks();
}