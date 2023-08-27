#ifndef NOTIFICATION_POLICY
#define NOTIFICATION_POLICY

#include "measurement.hpp"
#include "time_manager.cpp"

class NotificationPolicy
{
private:
    TimeManager timeManager = TimeManager();
    bool heatNotificationSentToday = false;
    bool coolNotificationSentToday = false;

public:
    NotificationPolicy()
    {
    }

    bool notifyOfSmoke(const Measurement &measurement)
    {
        if(timeManager.isTimeInRange(9, 23) && measurement.getCorrectedPPM() > 3.0) // ppm over 3.0
        {
          return true;
        }
        return false;
    }

    bool notifyOfCalibration(const Measurement &measurement)
    {
      if(timeManager.isTimeInRange(5, 6) && measurement.getRZero() > 0.0) // only between 5-6:00
      {
        return true;
      }
      return false;
    }

    bool notifyOfHeat(const Measurement &measurement)
    {
      if(!heatNotificationSentToday && measurement.readTemperature() > 27.0) // °C
      {
        heatNotificationSentToday = true;
        coolNotificationSentToday = false;
        return true;
      }
      return false;
    }
    bool notifyOfCool(const Measurement &measurement)
    {
      if(!coolNotificationSentToday && measurement.readTemperature() < 22.0) // °C
      {
        heatNotificationSentToday = false;
        coolNotificationSentToday = true;
        return true;
      }
      return false;
    }
};

#endif
