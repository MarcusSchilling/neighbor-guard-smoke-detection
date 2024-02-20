#ifndef MAIN
#define MAIN

#include "observer/observer.cpp"
#include "observer/smoke_notifier.cpp"
#include "observer/data_logger.cpp"
#include "observer/temperature_notifier.cpp"
#include "observer/humidity_notifier.cpp"

// Networking
#include "infrastructure/wifi_connection.h"
#include "infrastructure/ota.h"

#include <FastBot.h>
#include "notification/message_reply.cpp"

// Configuration Files
#include "configuration/constants.h"
#include "configuration/shared.credentials.h"
#include "configuration/config.h"

// General Sensor Configuration
#include "domain/measurement.hpp"

// Sensor MQ135
#include <MQ135.h>

// Sensor DHT11
#include <DHT.h>

WifiConnection wifiConnection{};
DHT hygroSensor = DHT(DIGITALPIN, DHTTYPE);

bool isCalibration = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BUADRATE);
  wifiConnection.connectWiFi();
  initializeOTA();
  setupMessageReply();

  Serial.println("Ready");

  Subject subject;
  Observer *telegramNotifier = new SmokeNotifier();
  Observer *dataLogger = new DataLogger();
  Observer *temperatureNotifier = new TemperatureNotifier();
  Observer *humidityNotifier = new HumidityNotifier();
  subject.attach(telegramNotifier);
  subject.attach(temperatureNotifier);
  subject.attach(humidityNotifier);
  subject.attach(dataLogger);
  while (isCalibration) {
    // Initialization & Calibration
    Serial.println("Initialization started");
    hygroSensor.begin();  // Begin DHT11 sensor communication
    Serial.println("DHT11 initialization complete");
    float temperature = hygroSensor.readTemperature();
    float humidity = hygroSensor.readHumidity();
    bool hygroSuccess = !(isnan(humidity) || isnan(temperature));
    if (hygroSuccess) {
      float rz = gasSensor.getRZero();
      float crz = gasSensor.getCorrectedRZero(temperature, humidity);
      float ppm = gasSensor.getPPM();
      float cppm = gasSensor.getCorrectedPPM(temperature, humidity);
      float resistance = gasSensor.getResistance();
      Measurement measurementHygro(SensorType::DHT, rz, crz, ppm, cppm, resistance, temperature, humidity);
      Measurement measurementGas(SensorType::MQ135, rz, crz, ppm, cppm, resistance, temperature, humidity);
      Serial.println("Initialization success!");
      isCalibration = false;
      break;
    } else {
      return;
    }
  }

  while (true) {
    handleOTA();
    tick();
    Serial.println("Measurement started");
    float temperature = DEFAULT_TEMP;
    float humidity = DEFAULT_HUM;
    float rz = gasSensor.getRZero();
    float crz = gasSensor.getCorrectedRZero(temperature, humidity);
    float ppm = gasSensor.getPPM();
    float cppm = gasSensor.getCorrectedPPM(temperature, humidity);
    float resistance = gasSensor.getResistance();
    if (isUseHygro) {
      Serial.println("... using Hygrometer");
      temperature = hygroSensor.readTemperature();
      humidity = hygroSensor.readHumidity();
      cppm = gasSensor.getCorrectedPPM(temperature, humidity);
      crz = gasSensor.getCorrectedRZero(temperature, humidity);
    }
    Measurement measurementHygro(SensorType::DHT, rz, crz, ppm, cppm, resistance, temperature, humidity);
    Measurement measurementGas(SensorType::MQ135, rz, crz, ppm, cppm, resistance, temperature, humidity);

    subject.notify(measurementGas);
    subject.notify(measurementHygro);
    delay(1000 / s_updateRate);
  }
}

void loop() {
}
#endif
