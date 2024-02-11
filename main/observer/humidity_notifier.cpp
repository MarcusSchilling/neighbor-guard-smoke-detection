#ifndef HUMIDITY_NOTIFIER_CPP
#define HUMIDITY_NOTIFIER_CPP

#include "observer.cpp"
#include "../domain/measurement.hpp"

class HumidityNotifier : public Observer
{
public:
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