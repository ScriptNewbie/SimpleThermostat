#include "temperatureSensor.h"
#include <Arduino.h>

void TemperatureSensor::measureTemperature() {
    sensors.requestTemperatures();
    temperatures[currentIndex] = sensors.getTempCByIndex(0);
    currentIndex = (currentIndex + 1) % 3;
}

float TemperatureSensor::getTemperature() {
    float sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += temperatures[i];
    }
    return sum / 3;
}

void TemperatureSensor::setup() {
    sensors.begin();

    for (int i = 0; i < 3; ++i) {
        sensors.requestTemperatures();
        temperatures[i] = sensors.getTempCByIndex(0);
    }
}

void TemperatureSensor::tasks() {
    unsigned long now = millis();
    if(now - lastMeasurement > 1000 * 5){
        lastMeasurement = now;
        measureTemperature();
    }
}