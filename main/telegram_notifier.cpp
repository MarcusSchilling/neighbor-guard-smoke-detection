#ifndef TELEGRAM_NOTIFIER
#define TELEGRAM_NOTIFIER

#include "constants.h"
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
        // Smoke detected via ppm value
        if (measurement.getSensor() == SensorType::MQ135 && notificationPolicy.notifyOfSmoke(measurement))
        {
            if(!isConstantMQ135Notify)
                {
                    telegramBot.sendMessage("SMOKE detected!");
                }
            telegramBot.sendMessage(
                String(
                    "\nSensor MQ135 \nPPM: " + String(measurement.getPPM()) +
                    " ppm \nRAW Resistance: " + String(measurement.getResistance()) +
                    " Ohm \nCorrected PPM: " + String(measurement.getCorrectedPPM()) +
                    " ppm"
                )
            );
        }
        // Calibration: RZero values
        if(measurement.getSensor() == SensorType::MQ135 && notificationPolicy.notifyOfCalibration(measurement))
        {
            telegramBot.sendMessage("Calibration values:");
            telegramBot.sendMessage(
                String(
                    "\nSensor MQ135 \nRZero: " + String(measurement.getRZero()) +
                    " Ohm \nCorrected RZero: " + String(measurement.getCorrectedRZero()) +
                    " Ohm"
                )
            );
        }
        // Humidity & Temperature values
        if(measurement.getSensor() == SensorType::DHT && notificationPolicy.notifyOfHeat(measurement))
        {
            telegramBot.sendMessage("Heat WARNING today!");
            telegramBot.sendMessage(
                String(
                    "\nSensor DHT11 \nTemp: " + String(measurement.readTemperature()) +
                    " C \nHumidity: " + String(measurement.readHumidity()) +
                    " %"
                )
            );
        }
        else if(measurement.getSensor() == SensorType::DHT && notificationPolicy.notifyOfCool(measurement))
        {
            telegramBot.sendMessage("Cooled down enough to air out. Watch for humidity & smoke WARNING...");
            telegramBot.sendMessage(
                String(
                    "\nSensor DHT11 \nTemp: " + String(measurement.readTemperature()) +
                    " C \nHumidity: " + String(measurement.readHumidity()) +
                    " %"
                )
            );
        }
        if(measurement.getSensor() == SensorType::DHT && notificationPolicy.notifyOfHumidity(measurement))
        {
            telegramBot.sendMessage(
                String(
                    "\nSensor DHT11 \nTemp: " + String(measurement.readTemperature()) +
                    " C \nHumidity: " + String(measurement.readHumidity()) +
                    " %"
                )
            );
        }
    }
};
#endif