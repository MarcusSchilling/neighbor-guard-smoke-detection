#include "telegram_bot.cpp"

// Sensor MQ135
#include "MQ135.h"
const int ANALOGPIN=0;
MQ135 gasSensor = MQ135(ANALOGPIN);

TelegramBot telegramBot;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize the Serial monitor with the baud rate 115200
  telegramBot.initialize();
  while (true)
  {
    loop();
    delay(15000);
  }
}

void loop()
{
  // read the input on analog pin 0:
  float ppm = gasSensor.getPPM();
  float resistance = gasSensor.getResistance();
  // print out the value you read:
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  // send sensor readouts to telegram bot
  telegramBot.sendMessage(String("Sensor MQ135 Readout\n PPM: " + String(ppm) + "\n RAW Resistance: " + String(resistance)));
}
