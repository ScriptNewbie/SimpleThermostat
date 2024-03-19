#include "temperatureSensor.h"

void TemperatureSensor::measureTemperature() {
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
        temperatures[i] = sensors.getTempCByIndex(0);
    }

    ticker.attach(5, std::bind(&TemperatureSensor::measureTemperature, this));
}