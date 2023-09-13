# Setup

Create file credentials.h in the main folder. Containing the following variables.
```cpp
#define WIFI_SSID "WLAN-NAME"
#define WIFI_PASS "WLAN-PASSWORD"
#define BOT_TOKEN "TOKEN-Telegram-Bot"
#define CHAT_ID "Chat-ID-Telegram"
```

# Installation
Use the Arduino IDE

## Install in Boards Manager:
- [ESP8266 Boards](https://github.com/esp8266/Arduino)

## Driver Required
- CH340g Driver

## Install Libraries:
- [MQ135](https://github.com/NuclearPhoenixx/MQ135) --> Version 1.1.1
- [FastBot](https://github.com/GyverLibs/FastBot) --> Version 2.26
- [NTPClient](https://github.com/arduino-libraries/NTPClient) --> Version 3.2.1
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) --> Version 1.4.4
- [ArduinoOTA](https://github.com/jandrassy/ArduinoOTA) --> Version 1.0.11