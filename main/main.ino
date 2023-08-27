#ifndef MAIN
#define MAIN

#include "measurement.hpp"
#include "observer.cpp"
#include "telegram_notifier.cpp"

// Sensor MQ135
#include "MQ135.h"
const int ANALOGPIN = 0;
MQ135 gasSensor = MQ135(ANALOGPIN);

// Sensor DHT11
#include <DHT.h>
const int DIGITALPIN = D2;
const int DHTTYPE = DHT11; // DHT11 or DHT22, depends on your sensor
DHT hygroSensor = DHT(DIGITALPIN, DHTTYPE);
bool isUseHygro = true;  // Set to false to only use gas sensor
bool isCalibration = true; // Set to false to skip gas sensor calibration 
                          // IMPORTANT! For true a hygrometer sensor MUST be attached

float rz = 0.0;
float crz = 0.0;
float ppm = 0.0;
float cppm = 0.0;
float resistance = 0.0;
float temperature = 0.0;
float humidity = 0.0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize the Serial monitor with the baud rate 115200
  Subject subject;
  Observer *telegramNotifier = new TelegramNotifier();
  subject.attach(telegramNotifier);
  while (isCalibration)
  {
    // Initialization & Calibration
    Serial.println("Initialization started");
    hygroSensor.begin(); // Begin DHT11 sensor communication
    Serial.println("DHT11 initialization complete");
    temperature = hygroSensor.readTemperature();
    humidity = hygroSensor.readHumidity();
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Measurement measurementHygro(SensorType::DHT, 0.0, 0.0, 0.0, 0.0, 0.0, temperature, humidity);
    bool hygroSuccess = !(isnan(humidity) || isnan(temperature));
    Serial.println(String(hygroSuccess));
    if(hygroSuccess)
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
    Serial.println("Measurement started");
    float cppm = gasSensor.getCorrectedPPM(22.0, 50.0); // 22°C & 50% Humidity as defaults
    if(isUseHygro)
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
    
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Resistance: ");
    Serial.println(resistance);
    Serial.print("PPM: ");
    Serial.print(ppm);
    Serial.println(" ppm");
    Serial.print("Corrected PPM: ");
    Serial.print(cppm);
    Serial.println(" ppm");
    Serial.print("RRero: ");
    Serial.print(rz);
    Serial.println(" Ohm");
    Serial.print("Corrected RZero: ");
    Serial.print(crz);
    Serial.println(" Ohm");

    subject.notify(measurementGas);
    subject.notify(measurementHygro);
    delay(15000);
    }
}

void loop()
{
}
#endif
