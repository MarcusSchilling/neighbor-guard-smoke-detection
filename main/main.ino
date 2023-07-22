#include "telegram_bot.cpp"

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
  telegramBot.sendMessage("Hello");
}
