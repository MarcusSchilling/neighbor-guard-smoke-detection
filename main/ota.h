#ifndef OTA_H
#define OTA_H

#include <ArduinoOTA.h>

void initializeOTA()
{
    ArduinoOTA.setHostname(ESP_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASS);
    ArduinoOTA.setPort(8266);
    ArduinoOTA.onStart([]()
                       { Serial.println("Start"); });
    ArduinoOTA.onEnd([]()
                     { Serial.println("\nEnd"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed"); });
    ArduinoOTA.begin();
}

void handleOTA()
{
    ArduinoOTA.handle();
}


#endif