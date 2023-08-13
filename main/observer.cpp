#ifndef OBSERVER
#define OBSERVER

#include <iostream>
#include <vector>
#include "measurement.hpp"

class Observer
{
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