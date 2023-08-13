#ifndef TELEGRAM_NOTIFIER
#define TELEGRAM_NOTIFIER
#include "observer.cpp"
#include "telegram_bot.cpp"
#include "notification_policy.cpp"
class TelegramNotifier : public Observer
{
public:
    TelegramBot telegramBot;
    NotificationPolicy notificationPolicy;

    TelegramNotifier()
    {
        telegramBot.initialize();
    }

    void update(const Measurement &measurement) override
    {
        if (measurement.getSensor() == SensorType::MQ135 && notificationPolicy.shouldNotify(measurement))
        {
            telegramBot.sendMessage(String("Sensor MQ135 \nPPM: " + String(measurement.getPM()) + "\nRAW Resistance: " + String(measurement.getResistance())));
        }
    }
};
#endif