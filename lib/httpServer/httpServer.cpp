#include <Arduino.h>
#include "httpServer.h"
#include "eePromTools.h"
#include "clock.h"

extern String ssid;
extern String wpa;
extern float temperatureHotter;
extern float temperatureNormal;
extern String hotterPeriodStart;
extern String hotterPeriodEnd;

extern float currentTemperature;
extern Clock timeClock;

void HttpServer::handleDataGet(){
    doc.clear();
    doc["ip"] = WiFi.localIP().toString();
    doc["temperature"] = currentTemperature;
    doc["time"] = timeClock.getTimeString();
    doc["heatingProfile"] = timeClock.currentTimeInRange(hotterPeriodStart, hotterPeriodEnd) ? "hotter" : "normal";

    char output[1024];
    serializeJsonPretty(doc, output);
    server.send(200, "application/json", output);
};

String HttpServer::generateCurrentSettingsString(){
    doc.clear();
    doc["ssid"] = ssid;
    doc["wpa"] = wpa;
    doc["temperatureHotter"] = temperatureHotter;
    doc["temperatureNormal"] = temperatureNormal;
    doc["hotterPeriodStart"] = hotterPeriodStart;
    doc["hotterPeriodEnd"] = hotterPeriodEnd;

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
            temperatureHotter = doc["temperatureHotter"].as<float>();
            eepromWrite(TEMPERATURE_HOTTER_START, String(temperatureHotter));
        }

        if (doc.containsKey("temperatureNormal"))
        {
            temperatureNormal = doc["temperatureNormal"].as<float>();
            eepromWrite(TEMPERATURE_NORMAL_START, String(temperatureNormal));
        }

        if (doc.containsKey("hotterPeriodStart"))
        {
            hotterPeriodStart = doc["hotterPeriodStart"].as<String>();
            eepromWrite(HOTTER_PERIOD_START_START, hotterPeriodStart);
        }

        if (doc.containsKey("hotterPeriodEnd"))
        {
            hotterPeriodEnd = doc["hotterPeriodEnd"].as<String>();
            eepromWrite(HOTTER_PERIOD_END_START, hotterPeriodEnd);
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