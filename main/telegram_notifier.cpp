#ifndef TELEGRAM_NOTIFIER
#define TELEGRAM_NOTIFIER
#include "observer.cpp"
#include "telegram_bot.cpp"

class TelegramNotifier : public Observer
{
public:
    TelegramBot telegramBot;

    TelegramNotifier()
    {
        telegramBot.initialize();
    }

    void update(const Measurement &measurement) override
    {
        if (measurement.getSensor() == SensorType::MQ135)
        {
            telegramBot.sendMessage(String("Sensor MQ135 \nPPM: " + String(measurement.getPM()) + "\nRAW Resistance: " + String(measurement.getResistance())));
        }
    }
};
#endif