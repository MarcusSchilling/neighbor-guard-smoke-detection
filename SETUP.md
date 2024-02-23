# Setup

Create file credentials.h in the ```main/configuration``` folder. Containing the following variables as well as anything confidential.
```cpp
// ------------------ WiFi ------------------
#define WIFI_SSID "WIFI-NAME"
#define WIFI_PASS "WIFI-PASSWORD"
#define ESP_HOSTNAME "HOSTNAME"
#define OTA_PASS "PASSWORD-FOR-OTA"

// ------------------ Telegram Bot ------------------
#define BOT_TOKEN "TOKEN-Telegram-Bot"
#define CHAT_ID "Chat-ID-Telegram"

// ------------------ InfluxDB ------------------
// only when using your own influxDB server, otherwise see shared.credentials.h
#define INFLUXDB_ORG "ORGANIZATION_NAME"
#define INFLUXDB_DATABASE "DATABASE_NAME"
#define INFLUXDB_PORT "8086"
#define INFLUXDB_URL "http://URL:8086"
#define INFLUXDB_USER "USERNAME"
#define INFLUXDB_PWD "LOGIN_PASSWORD"
#define INFLUXDB_TOKEN "API_TOKEN"
#define INFLUXDB_BUCKET "BUCKET_NAME"
#define NAMESPACE "NAMESPACE_FOR_BUCKET_CREATION"
```
Create file shared.credentials.h in the ```main/configuration``` folder. Containing the following variables as well as any shared credentials (i.e. shared influxDB instance).
```cpp

// ------------------ InfluxDB ------------------
#define INFLUXDB_BUCKET_NAME NAMESPACE INFLUXDB_BUCKET

// when using a shared influxDB server
// this will overwrite variables defined in credentials.h
#define INFLUXDB_ORG "ORGANIZATION_NAME"
#define INFLUXDB_DATABASE "DATABASE_NAME"
#define INFLUXDB_PORT "PORT"
#define INFLUXDB_URL "http://URL:INFLUXDB_PORT"
#define INFLUXDB_USER "USERNAME"
#define INFLUXDB_PWD "LOGIN_PASSWORD"
#define INFLUXDB_TOKEN "API_TOKEN"
#define INFLUXDB_BUCKET "BUCKET_NAME"
#define NAMESPACE "NAMESPACE_FOR_BUCKET_CREATION"
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
- [InfluxDBClient](https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino) --> Version 3.13.1

# InfluxDB Server Installation
For simplification a docker-compose can be found in /docker.
For this to work add a .env file in the /docker directory with the following variables:
```yaml
INFLUXDB_ORG=SmokeGuard
INFLUXDB_PORT=8086
INFLUXDB_DATABASE=smokeguardDB
INFLUXDB_BUCKET=smokeGuardBucket
INFLUXDB_USER=smokeguard
INFLUXDB_PWD=<Add your password here>
INFLUXDB_TOKEN=<Add your influxdb token here>
PARENT_WORKING_DIRECTORY=<Add your desired influxdb data directory here>
```