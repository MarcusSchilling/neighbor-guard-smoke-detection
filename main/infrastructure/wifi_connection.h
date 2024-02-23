#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include "../configuration/shared.credentials.h"
#include <ESP8266WiFi.h>

class WifiConnection
{
public:
    bool hasConnection()
    {
        return WiFi.status() != WL_CONNECTED;
    }

    void connectWiFi()
    {
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        while (hasConnection())
        {
            delay(500);
            Serial.print(".");
            if (millis() > 15000)
                ESP.restart();
        }
    }
};
#endif