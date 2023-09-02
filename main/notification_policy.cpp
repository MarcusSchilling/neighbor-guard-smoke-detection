#ifndef NOTIFICATION_POLICY
#define NOTIFICATION_POLICY

#include "constants.h"
#include "measurement.hpp"
#include "time_manager.cpp"

class NotificationPolicy
{
private:
    TimeManager timeManager = TimeManager();
    bool  isHeatNotificationSent = false;
    bool isCoolNotificationSent = false;
    bool isWetNotificationSent = false;

public:
    NotificationPolicy()
    {
    }

    bool notifyOfSmoke(const Measurement &measurement)
    {
        if(measurement.getSensor() == SensorType::MQ135 && (timeManager.isTimeInRange(TIME_START_SMOKE_DETECTION, TIME_END_SMOKE_DETECTION) && measurement.getCorrectedPPM() > THRESHOLD_CPPM) || isConstantMQ135Notify)
        {
          return true;
        }
        return false;
    }

    bool notifyOfCalibration(const Measurement &measurement)
    {
      if(measurement.getSensor() == SensorType::MQ135 && timeManager.isTimeInRange(TIME_START_CALIBRATION, TIME_END_CALIBRATION) && measurement.getRZero() > THRESHOLD_LOWER_CALIBRATION
        && measurement.getRZero() < THRESHOLD_UPPER_CALIBRATION && isCalibrateSensor)
      {
        return true;
      }
      return false;
    }

    bool notifyOfHeat(const Measurement &measurement)
    {
      if(measurement.getSensor() == SensorType::DHT && !isHeatNotificationSent && measurement.readTemperature() > THRESHOLD_HEAT)
      {
        isHeatNotificationSent = true;
        return true;
      }
      else if(isHeatNotificationSent && measurement.readTemperature() < THRESHOLD_HEAT)
      {
        isHeatNotificationSent = false;
      }
      return false;
    }
    bool notifyOfCool(const Measurement &measurement)
    {
      if(measurement.getSensor() == SensorType::DHT && !isCoolNotificationSent && measurement.readTemperature() < THRESHOLD_COOL)
      {
        isCoolNotificationSent = true;
        return true;
      }
      else if(isCoolNotificationSent && measurement.readTemperature() > THRESHOLD_COOL)
      {
        isCoolNotificationSent = false;
      }
      return false;
    }
    bool notifyOfHumidity(const Measurement &measurement)
    {
      if(measurement.getSensor() == SensorType::DHT && !isWetNotificationSent && measurement.readHumidity() > THRESHOLD_HUM)
      {
        isWetNotificationSent = true;
        return true;
      }
      else if(isWetNotificationSent && measurement.readHumidity() < THRESHOLD_HUM)
      {
        isWetNotificationSent = false;
        return true;
      }
      return false;
    }
};

#endif
