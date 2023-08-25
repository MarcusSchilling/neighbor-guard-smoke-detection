#ifndef TELEGRAM_BOT
#define TELEGRAM_BOT

#include <FastBot.h>
#include "credentials.h"

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

class TelegramBot
{
private:
    FastBot fastBot{BOT_TOKEN};
    WifiConnection wifiConnection{};

public:
    TelegramBot()
    {
        fastBot.setChatID(CHAT_ID);
    }

    void initialize()
    {
        wifiConnection.connectWiFi();
    }

    void sendMessage(String message)
    {
        fastBot.sendMessage(message);
    }
};
#endif