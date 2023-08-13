#ifndef MAIN
#define MAIN

#include "measurement.hpp"
#include "observer.cpp"
#include "telegram_notifier.cpp"

// Sensor MQ135
#include "MQ135.h"
const int ANALOGPIN = 0;
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize the Serial monitor with the baud rate 115200
  Subject subject;
  Observer *telegramNotifier = new TelegramNotifier();
  subject.attach(telegramNotifier);
  while (true)
  {
    float ppm = gasSensor.getPPM();
    float resistance = gasSensor.getResistance();
    Measurement measurement(SensorType::MQ135, ppm, resistance);
    subject.notify(measurement);
    delay(15000);
  }
}

void loop()
{
}
#endif