#include "heater.h"
#include "eePromTools.h"

#define HEATER_PIN 5

void Heater::setup()
{
    timeClock.setup();
    temperatureSensor.setup();
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
    regulateTemperature();
}

void Heater::startHeating()
{
    digitalWrite(HEATER_PIN, HIGH);
}

void Heater::stopHeating()
{
    digitalWrite(HEATER_PIN, LOW);
}

bool Heater::isHeating()
{
    return digitalRead(HEATER_PIN);
}

void Heater::regulateTemperature()
{
    float targetTemperature = timeClock.currentTimeInRange(hotterPeriodStart, hotterPeriodEnd) ? temperatureHotter : temperatureNormal;
    float currentTemperature = temperatureSensor.getTemperature();

    if (isHeating() && currentTemperature > targetTemperature + hysteresis)
    {
        return stopHeating();
    }
    if (!isHeating() && currentTemperature < targetTemperature - hysteresis)
    {
        return startHeating();
    }
}