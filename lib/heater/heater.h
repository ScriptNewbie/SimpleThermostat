#pragma once
#include <Arduino.h>
#include "clock.h"
#include "temperatureSensor.h"

class Heater
{
public:
    Clock timeClock;
    TemperatureSensor temperatureSensor;
    String hotterPeriodStart;
    String hotterPeriodEnd;
    float temperatureHotter;
    float temperatureNormal;
    float hysteresis;
    void setup();
    void tasks();
};