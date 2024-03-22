#pragma once
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <time.h>


class Clock
{
    public:
        Clock() : timeClient(ntpUDP) {};
        void tasks();
        void setup();
        String getTimeString();
        bool currentTimeInRange(String start, String end);

    private:
        WiFiUDP ntpUDP;
        NTPClient timeClient;
        bool isSummerTime();
        
};