#ifndef SMOKE_NOTIFIER_CPP
#define SMOKE_NOTIFIER_CPP

#include "../configuration/constants.h"
#include "observer.cpp"
#include "../notification/telegram_bot.cpp"
#include "../notification/notification_policy.cpp"
#include "../domain/measurement.hpp"
#include "../configuration/config.h"

class SmokeNotifier : public Observer
{
private:
    bool isAlwaysNotifySmoke = s_notificationState == 11 || s_notificationState == 12;

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
            if (!isAlwaysNotifySmoke)
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