# What is it?

It's a repo containing software to create a simple ESP8266 (ESP-12E/NodeMCU) and DS18B20 based thermostat. 

# Device

Connect DS18B20 temperature sensor to chosen ESP-12E GPIO pin. Also pick another pin for controlling heater (this pin will be either HIGH when heater should be enabled and LOW when heater should be disabled). 

# Firmware

Firmware is written using Platform.IO and Arduino framework. It is in a "firmware" directory of this repo.

Go to lib/heater/heater.cpp and set GPIO pin you wish to be a heater output by modifing HEATER_PIN define statement.

Go to lib/temperatureSensor/temperatureSensor.h to set pin you have a DS18B20 tempearture sensor connected to by modifing TEMPERATURE_SENSOR_PIN define statement.

# Initial device configuration

After flashing a firmware to a new device, it's EEPROM contains garbage, meaning it won't be able to connect to your WiFi.

It's the same situation as if device looses WiFi connection. Changing configuration in such state is described bellow.

# Reaching the device

When device looses the connection with your WiFi AP, it starts it's own passwordless hotspot with SSID "Boiler". It's IP address in this self hosted newtork is 192.168.4.1.

When connected to your WiFi, device has IP address assigned by your DHCP server. 

It also starts mDSN responder while connected to your WiFi AP so it should be reachable via *boiler.local* mnemonic.

# Getting data and changing configuration

Device runs HTTP server with two API endpoints.

## Resource /data

### GET

Result of HTTP GET request to this resource is JSON encoded data in the following form:

    {
      "ip": "192.168.1.200",
      "temperature": 20.2,
      "time": "14:15",
      "heating": false,
      "targetTemperature": 20
    }

Where:\
**ip** is current device's IP address in your network,\
**temperature** is current temperature,\
**time** is current time,\
**heating** says whether heater is turned on or off,\
**targetTemperature** is current target temperature (*temperature +- hysteresis* device tries to keep on current time)

## Resource /settings

### GET 

Result of HTTP GET request to this resource is JSON encoded data in the following form:

    {
      "ssid": "WiFiSSID",
      "wpa": "WiFiPassword",
      "hysteresis": 1,
      "defaultTemperature": 18,
      "heatingPeriods": [
          {
              "start": "19:00",
              "end": "23:00",
              "temperature": 20
          },
          {
              "start": "23:00",
              "end": "05:00",
              "temperature": 10
          }
      ]
    }
### POST

HTTP POST request's body to this resource should contain JSON with parameters you wish to change eg.:

    {
      "hysteresis": 1,
      "defaultTemperature": 18
      "heatingPeriods": [
          {
              "start": "10:00",
              "end": "20:00",
              "temperature": 50
          }
        ]
    }
Response looks the same as a response to GET request, but with updated settings.

# How exactly does it work?

By sending requests to described above API, you set hysteresis and default target temperature (by setting *defaultTemperature*), you can also specify periods at which target temperature is different than default (*heatingPeriod* array).

Device will try to keep the temperature between (target temperature - hysteresis) and (target temperature + hysteresis) by either turning on or off the heater (HIGH or LOW on specified GPIO pin).

# App

TBA
