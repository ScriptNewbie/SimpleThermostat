#include <Arduino.h>
#include "httpServer.h"
#include "eePromTools.h"
#include "clock.h"
#include "heater.h"

extern String ssid;
extern String wpa;
extern Heater heater;


void HttpServer::handleDataGet(){
    doc.clear();
    doc["ip"] = WiFi.localIP().toString();
    doc["temperature"] = heater.temperatureSensor.getTemperature();
    doc["time"] = heater.timeClock.getTimeString();
    doc["heating"] = heater.isHeating();

    char output[1024];
    serializeJsonPretty(doc, output);
    server.send(200, "application/json", output);
};

String HttpServer::generateCurrentSettingsString(){
    doc.clear();
    doc["ssid"] = ssid;
    doc["wpa"] = wpa;
    doc["temperatureHotter"] = heater.temperatureHotter;
    doc["temperatureNormal"] = heater.temperatureNormal;
    doc["hysteresis"] = heater.hysteresis;
    doc["hotterPeriodStart"] = heater.hotterPeriodStart;
    doc["hotterPeriodEnd"] = heater.hotterPeriodEnd;
    

    char output[1024];
    serializeJsonPretty(doc, output);
    return String(output);
}

void HttpServer::handleSettingsGet()
{  
    server.send(200, "application/json", generateCurrentSettingsString());
}

void HttpServer::handleSettingsPost()
{
    if (server.hasArg("plain"))
    {
        String body = server.arg("plain");
        doc.clear();
        deserializeJson(doc, body);

        bool wifiSettingsChanged = false;

        if (doc.containsKey("ssid"))
        {
            ssid = doc["ssid"].as<String>();
            eepromWrite(SSID_START, ssid);
            wifiSettingsChanged = true;
        }

        if (doc.containsKey("wpa"))
        {
            wpa = doc["wpa"].as<String>();
            eepromWrite(WPA_START, wpa);
            wifiSettingsChanged = true;
        }

        if (doc.containsKey("temperatureHotter"))
        {
            heater.temperatureHotter = doc["temperatureHotter"].as<float>();
            eepromWrite(TEMPERATURE_HOTTER_START, String(heater.temperatureHotter));
        }

        if (doc.containsKey("temperatureNormal"))
        {
            heater.temperatureNormal = doc["temperatureNormal"].as<float>();
            eepromWrite(TEMPERATURE_NORMAL_START, String(heater.temperatureNormal));
        }

        if (doc.containsKey("hotterPeriodStart"))
        {
            heater.hotterPeriodStart = doc["hotterPeriodStart"].as<String>();
            eepromWrite(HOTTER_PERIOD_START_START, heater.hotterPeriodStart);
        }

        if (doc.containsKey("hotterPeriodEnd"))
        {
            heater.hotterPeriodEnd = doc["hotterPeriodEnd"].as<String>();
            eepromWrite(HOTTER_PERIOD_END_START, heater.hotterPeriodEnd);
        }
        
        if (doc.containsKey("hysteresis"))
        {
            heater.hysteresis = doc["hysteresis"].as<float>();
            eepromWrite(HYSTERESIS_START, String(heater.hysteresis));
        }

        server.send(200, "application/json", generateCurrentSettingsString());

        if (wifiSettingsChanged)
        {
            delay(1000);
            WiFi.disconnect(true);
            WiFi.begin(ssid.c_str(), wpa.c_str());
        }
    }

    server.send(400, "application/json", "{\"error\": \"Invalid request\"}");
}

void HttpServer::setup()
{

    httpUpdater.setup(&server);
    server.on("/settings", HTTP_GET, std::bind(&HttpServer::handleSettingsGet, this));
    server.on("/settings", HTTP_POST, std::bind(&HttpServer::handleSettingsPost, this));
    server.on("/data", HTTP_GET, std::bind(&HttpServer::handleDataGet, this));
    server.begin();
}

void HttpServer::tasks()
{
    server.handleClient();
}