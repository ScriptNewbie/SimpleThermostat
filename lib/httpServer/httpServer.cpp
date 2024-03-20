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
    doc["targetTemperature"] = heater.getTargetTemperature();

    char output[1024];
    serializeJsonPretty(doc, output);
    server.send(200, "application/json", output);
};

String HttpServer::generateCurrentSettingsString(){
    doc.clear();
    doc["ssid"] = ssid;
    doc["wpa"] = wpa;
    doc["hysteresis"] = heater.hysteresis;
    doc["defaultTemperature"] = heater.defaultTemperature;

    JsonArray heatingPeriods = doc.createNestedArray("heatingPeriods");

    HeatingPeriod *periods = heater.getHeatingPeriods();
    for(int i = 0; i < heater.getHeatingPeriodsCount(); ++i){
        HeatingPeriod period = periods[i];
        heatingPeriods.add(period);
    }
    

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

        if(doc.containsKey("heatingPeriods")){
            JsonArray periods = doc["heatingPeriods"].as<JsonArray>();
            heater.setHeatingPeriods(periods);
        }
        
        if (doc.containsKey("hysteresis"))
        {
            heater.hysteresis = doc["hysteresis"].as<float>();
            eepromWrite(HYSTERESIS_START, String(heater.hysteresis));
        }

        if(doc.containsKey("defaultTemperature")){
            heater.defaultTemperature = doc["defaultTemperature"].as<float>();
            eepromWrite(DEFAULT_TEMPERATURE_START, String(heater.defaultTemperature));
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