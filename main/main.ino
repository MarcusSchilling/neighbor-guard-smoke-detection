#ifndef MAIN
#define MAIN

#include "observer/observer.cpp"
#include "observer/smoke_notifier.cpp"
#include "observer/temperature_notifier.cpp"
#include "observer/humidity_notifier.cpp"

// Networking
#include "infrastructure/wifi_connection.h"
#include "infrastructure/ota.h"

#include <FastBot.h>
#include "notification/message_reply.cpp"

// Configuration Files
#include "configuration/constants.h"
#include "configuration/credentials.h"

// General Sensor Configuration
#include "domain/measurement.hpp"

// Sensor MQ135
#include <MQ135.h>
MQ135 gasSensor = MQ135(ANALOGPIN, RZEROCALIBRATION); // calibrated sensor

// Sensor DHT11
#include <DHT.h>

WifiConnection wifiConnection{};
DHT hygroSensor = DHT(DIGITALPIN, DHTTYPE);

float rz = 0.0;
float crz = 0.0;
float ppm = 0.0;
float cppm = 0.0;
float resistance = 0.0;
float temperature = 0.0;
float humidity = 0.0;
bool isCalibration = true;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BUADRATE);
  wifiConnection.connectWiFi();
  initializeOTA();
  setupMessageReply();

  Serial.println("Ready");

  Subject subject;
  Observer *telegramNotifier = new SmokeNotifier();
  Observer *temperatureNotifier = new TemperatureNotifier();
  Observer *humidityNotifier = new HumidityNotifier();
  subject.attach(telegramNotifier);
  subject.attach(temperatureNotifier);
  subject.attach(humidityNotifier);
  while (isCalibration)
  {
    // Initialization & Calibration
    Serial.println("Initialization started");
    hygroSensor.begin(); // Begin DHT11 sensor communication
    Serial.println("DHT11 initialization complete");
    temperature = hygroSensor.readTemperature();
    humidity = hygroSensor.readHumidity();
    Measurement measurementHygro(SensorType::DHT, 0.0, 0.0, 0.0, 0.0, 0.0, temperature, humidity);
    bool hygroSuccess = !(isnan(humidity) || isnan(temperature));
    Serial.println(String(hygroSuccess));
    if (hygroSuccess)
    {
      rz = gasSensor.getRZero();
      crz = gasSensor.getCorrectedRZero(temperature, humidity);
      ppm = gasSensor.getPPM();
      cppm = gasSensor.getCorrectedPPM(temperature, humidity);
      resistance = gasSensor.getResistance();
      Measurement measurementGas(SensorType::MQ135, rz, crz, ppm, cppm, resistance);
      Serial.println("Initialization success!");
      isCalibration = false;
      break;
    }
    else
    {
      return;
    }
  }

  while (true)
  {
    handleOTA();
    tick();
    Serial.println("Measurement started");
    float cppm = gasSensor.getCorrectedPPM(DEFAULT_TEMP, DEFAULT_HUM);
    if (isUseHygro)
    {
      Serial.println("... using Hygrometer");
      temperature = hygroSensor.readTemperature();
      humidity = hygroSensor.readHumidity();
      cppm = gasSensor.getCorrectedPPM(temperature, humidity);
      crz = gasSensor.getCorrectedRZero(temperature, humidity);
    }
    Measurement measurementHygro(SensorType::DHT, 0.0, 0.0, 0.0, 0.0, 0.0, temperature, humidity);
    rz = gasSensor.getRZero();
    ppm = gasSensor.getPPM();
    resistance = gasSensor.getResistance();
    Measurement measurementGas(SensorType::MQ135, rz, crz, ppm, cppm, resistance);

    subject.notify(measurementGas);
    subject.notify(measurementHygro);
    delay(DELAYTIME);
  }
}

void loop()
{
}
#endif
