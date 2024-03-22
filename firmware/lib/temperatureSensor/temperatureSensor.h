#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPERATURE_SENSOR_PIN 5

class TemperatureSensor {
    private: 
        OneWire oneWire;
        DallasTemperature sensors;
        void measureTemperature();
        float temperatures[3] = {0, 0, 0};
        int currentIndex = 0;
        unsigned long lastMeasurement = 0;
    public:
        TemperatureSensor() : oneWire(TEMPERATURE_SENSOR_PIN), sensors(&oneWire) {};
        void setup();
        void tasks();
        float getTemperature();
};
