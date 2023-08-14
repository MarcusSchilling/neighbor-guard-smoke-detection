#ifndef NOTIFICATION_POLICY
#define NOTIFICATION_POLICY

#include "measurement.hpp"
#include "time_manager.cpp"

class NotificationPolicy
{
private:
    TimeManager timeManager = TimeManager();

public:
    NotificationPolicy()
    {
    }

    bool shouldNotify(const Measurement &measurement)
    {
        return timeManager.isTimeInRange(9, 23) && measurement.getPM() > 5;
    }
};

#endif