#ifndef SMOKE_NOTIFIER
#define SMOKE_NOTIFIER

#include "constants.h"
#include "observer.cpp"
#include "telegram_bot.cpp"
#include "notification_policy.cpp"

class SmokeNotifier : public Observer
{
public:
    TelegramBot telegramBot;
    NotificationPolicy notificationPolicy;

    SmokeNotifier()
    {
        telegramBot.initialize();
    }

    void update(const Measurement &measurement) override
    {
        // Smoke detected via ppm value
        if (notificationPolicy.notifyOfSmoke(measurement))
        {
            if (!isConstantMQ135Notify)
            {
                telegramBot.sendMessage("SMOKE detected!");
            }
            telegramBot.sendMessage(
                String(
                    "\nSensor MQ135 \nPPM: " + String(measurement.getPPM()) +
                    " ppm \nRAW Resistance: " + String(measurement.getResistance()) +
                    " Ohm \nCorrected PPM: " + String(measurement.getCorrectedPPM()) +
                    " ppm"));
        }
        // Calibration: RZero values
        if (notificationPolicy.notifyOfCalibration(measurement))
        {
            telegramBot.sendMessage("Calibration values:");
            telegramBot.sendMessage(
                String(
                    "\nSensor MQ135 \nRZero: " + String(measurement.getRZero()) +
                    " Ohm \nCorrected RZero: " + String(measurement.getCorrectedRZero()) +
                    " Ohm"));
        }

    }
};
#endif