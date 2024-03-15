#pragma once

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

class HttpServer {
    private:
        ESP8266WebServer server;
        ESP8266HTTPUpdateServer httpUpdater;
        JsonDocument doc;
        void handleSettingsGet();
        void handleSettingsPost();
        void handleDataGet();
        String generateCurrentSettingsString();

    public:
        void setup();
        void tasks();
        HttpServer() : server(80) {};
};