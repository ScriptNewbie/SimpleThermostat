#include <ESP8266WiFi.h>
#include "configurationHotspot.h"

void ConfigurationHotspot::tasks()
{
    if (enabled)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            enabled = false;
            WiFi.softAPdisconnect(true);
        }
        return;
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        enabled = true;
        WiFi.softAP("Boiler");
    }
}