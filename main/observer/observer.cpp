#ifndef OBSERVER_CPP
#define OBSERVER_CPP

// #include <iostream>
#include <vector>
#include "../domain/measurement.hpp"
#include "../notification/notification_policy.cpp"
#include "../notification/telegram_bot.cpp"

static TelegramBot telegramBot;
static NotificationPolicy notificationPolicy;

class Observer
{
protected:
public:
    virtual void update(const Measurement &measurement) = 0;
};

class Subject
{
private:
    std::vector<Observer *> observers;

public:
    void attach(Observer *observer)
    {
        observers.push_back(observer);
    }

    void detach(Observer *observer)
    {
        for (auto it = observers.begin(); it != observers.end(); ++it)
        {
            if (*it == observer)
            {
                observers.erase(it);
                delete observer;
                break;
            }
        }
    }

    void notify(const Measurement &measurement)
    {
        for (Observer *observer : observers)
        {
            observer->update(measurement);
        }
    }
};
#endif