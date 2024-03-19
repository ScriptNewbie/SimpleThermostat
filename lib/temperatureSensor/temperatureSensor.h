#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>

class TemperatureSensor {
    private: 
        Ticker ticker;
        OneWire oneWire;
        DallasTemperature sensors;
        void measureTemperature();
        float temperatures[3] = {0, 0, 0};
        int currentIndex = 0;
    public:
        TemperatureSensor() : oneWire(2), sensors(&oneWire) {};
        void setup();
        float getTemperature();
};
