#ifndef TEMPERATURE_NOTIFIER_CPP
#define TEMPERATURE_NOTIFIER_CPP

#include "observer.cpp"
#include "../notification/notification_policy.cpp"
#include "../notification/telegram_bot.cpp"
#include "../domain/measurement.hpp"

class TemperatureNotifier : public Observer
{
public:
    NotificationPolicy notificationPolicy;
    TelegramBot telegramBot;

    TemperatureNotifier()
    {
        telegramBot.initialize();
    }

    void update(const Measurement &measurement) override
    {
        if (notificationPolicy.notifyOfHeat(measurement))
        {
            telegramBot.sendMessage("Heat WARNING today!");
            telegramBot.sendMessage(
                String(
                    "\nSensor DHT11 \nTemp: " + String(measurement.readTemperature()) +
                    " C \nHumidity: " + String(measurement.readHumidity()) +
                    " %"));
        }
        else if (notificationPolicy.notifyOfCool(measurement))
        {
            telegramBot.sendMessage("Cooled down enough to air out. Watch for humidity & smoke WARNING...");
            telegramBot.sendMessage(
                String(
                    "\nSensor DHT11 \nTemp: " + String(measurement.readTemperature()) +
                    " C \nHumidity: " + String(measurement.readHumidity()) +
                    " %"));
        }
    }
};

#endif