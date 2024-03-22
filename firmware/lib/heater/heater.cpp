#include "heater.h"
#include "eePromTools.h"

#define HEATER_PIN 8

void Heater::setup()
{
    pinMode(HEATER_PIN, OUTPUT);
    timeClock.setup();
    temperatureSensor.setup();
    hysteresis = eepromRead(HYSTERESIS_START, HYSTERESIS_END).toFloat();

    String heatingPeriodsString = eepromRead(HEATING_PERIODS_START, HEATING_PERIODS_END);

    JsonDocument doc;
    deserializeJson(doc, heatingPeriodsString);
    JsonArray periods = doc.as<JsonArray>();
    setHeatingPeriods(periods);
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
    float targetTemperature = getTargetTemperature();
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

bool convertToJson(const HeatingPeriod &period, JsonVariant variant)
{
    variant["start"] = period.start;
    variant["end"] = period.end;
    variant["temperature"] = period.temperature;
    return true;
}

void Heater::setHeatingPeriods(JsonArray periods)
{
    char buffer[1024];
    serializeJson(periods, buffer);
    eepromWrite(HEATING_PERIODS_START, String(buffer));

    int count = periods.size();
    HeatingPeriod *newHeatingPeriods = new HeatingPeriod[count];
    for (int i = 0; i < count; ++i)
    {
        HeatingPeriod period;
        period.start = periods[i]["start"].as<String>();
        period.end = periods[i]["end"].as<String>();
        period.temperature = periods[i]["temperature"].as<float>();
        newHeatingPeriods[i] = period;
    }
    delete[] heatingPeriods;
    heatingPeriodsCount = count;
    heatingPeriods = newHeatingPeriods;
}

float Heater::getTargetTemperature()
{
    for(int i = 0; i < heatingPeriodsCount; ++i){
        HeatingPeriod period = heatingPeriods[i];
        if(timeClock.currentTimeInRange(period.start, period.end)){
            return period.temperature;
        }
    }
    return defaultTemperature;
}