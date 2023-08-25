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
    const char time_start = timeManager.getEpochTime();
    char time_old = time_start;
    char time_now = time_start;

public:
    NotificationPolicy()
    {
    }

    bool notifyOfSmoke(const Measurement &measurement)
    {
        if(timeManager.isTimeInRange(9, 23) && measurement.getCorrectedPPM() > 3.0) // ppm over 3.0
        {
          time_now = timeManager.getEpochTime();
          if(abs(time_now-time_old) > 60*5) // every 5 Minutes
          {
            time_old = time_now;
            return true;
          }
        }
        return false;
    }

    bool notifyOfCalibration(const Measurement &measurement)
    {
      if(timeManager.isTimeInRange(23, 24)) // only between 23-24:00
      {
        time_now = timeManager.getEpochTime();
        if(abs(time_now-time_old) > 60*10) // every 10 Minutes
        {
          time_old = time_now;
          return true;
        }
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
      if(!coolNotificationSentToday && measurement.readTemperature() < 20.0) // °C
      {
        heatNotificationSentToday = false;
        coolNotificationSentToday = true;
        return true;
      }
      return false;
    }
};

#endif
