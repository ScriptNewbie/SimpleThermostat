#pragma once
#include <Arduino.h>
#include "clock.h"
#include "temperatureSensor.h"
#include <ArduinoJson.h>

struct HeatingPeriod
{
    String start;
    String end;
    float temperature;
};

bool convertToJson(const HeatingPeriod &period, JsonVariant variant);

class Heater
{
public:
    Clock timeClock;
    TemperatureSensor temperatureSensor;
    float defaultTemperature;
    float hysteresis;
    void setup();
    void tasks();
    bool isHeating();
    float getTargetTemperature();

    HeatingPeriod *getHeatingPeriods()
    {
        return heatingPeriods;
    }

    void setHeatingPeriods(JsonArray periods);

    Heater() : heatingPeriods(new HeatingPeriod[0]){};
    ~Heater()
    {
        delete[] heatingPeriods;
    }

    int getHeatingPeriodsCount()
    {
        return heatingPeriodsCount;
    }

private:
    void startHeating();
    void stopHeating();
    void regulateTemperature();
    HeatingPeriod *heatingPeriods;
    int heatingPeriodsCount = 0;
};