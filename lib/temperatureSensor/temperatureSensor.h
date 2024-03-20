#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor {
    private: 
        OneWire oneWire;
        DallasTemperature sensors;
        void measureTemperature();
        float temperatures[3] = {0, 0, 0};
        int currentIndex = 0;
        unsigned long lastMeasurement = 0;
    public:
        TemperatureSensor() : oneWire(2), sensors(&oneWire) {};
        void setup();
        void tasks();
        float getTemperature();
};
