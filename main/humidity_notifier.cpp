#ifndef HUMIDITY_NOTIFIER_CPP
#define HUMIDITY_NOTIFIER_CPP
#include "observer.cpp"
#include "notification_policy.cpp"
#include "telegram_bot.cpp"

class HumidityNotifier : public Observer
{
public:
    NotificationPolicy notificationPolicy;
    TelegramBot telegramBot;

    HumidityNotifier()
    {
        telegramBot.initialize();
    }

    void update(const Measurement &measurement) override
    {
        if (notificationPolicy.notifyOfHumidity(measurement))
        {
            telegramBot.sendMessage(
                String(
                    "\nSensor DHT11 \nTemp: " + String(measurement.readTemperature()) +
                    " C \nHumidity: " + String(measurement.readHumidity()) +
                    " %"));
        }
    }
};

#endif