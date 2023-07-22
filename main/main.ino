#include "credentials.h"
#include <FastBot.h>

FastBot bot(BOT_TOKEN);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize the Serial monitor with the baud rate 115200
  connectWiFi();
  setupBot();
  while (true)
  {
    loop();
    delay(15000);
  }
}

void setupBot()
{
  bot.setChatID(CHAT_ID);
  bot.attach(newMsg);
}

void connectWiFi()
{
  Serial.print(WIFI_SSID);
  Serial.print(WIFI_PASS);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (millis() > 15000)
      ESP.restart();
    Serial.println("Not Connected");
  }
  Serial.println("Connected");
}

void newMsg(FB_msg &msg)
{
  Serial.println(msg.toString());
}

void loop()
{
  // put your main code here, to run repeatedly:i
  bot.sendMessage("Hello, World!"); // Print "Hello, World!" to the Serial monitor
}
