#ifndef NOTIFICATION_POLICY_CPP
#define NOTIFICATION_POLICY_CPP

#include "../configuration/constants.h"
#include "../domain/measurement.hpp"
#include "../infrastructure/time_manager.cpp"
#include "../configuration/config.h"

class NotificationPolicy
{
private:
  TimeManager timeManager = TimeManager();
  bool isHeatNotificationSent = false;
  bool isCoolNotificationSent = false;
  bool isWetNotificationSent = false;
  bool isNotifySmoke = (s_notificationState != 0 || s_notificationState != 3) && (s_notificationState == 1 || s_notificationState == 2);
  bool isAlwaysNotifySmoke = s_notificationState == 11 || s_notificationState == 12;
  bool isNotifyHygro = (s_notificationState != 0 || s_notificationState != 2) && (s_notificationState == 1 || s_notificationState == 3);
  bool isAlwaysNotifyHygro = s_notificationState == 11 || s_notificationState == 13;
  String startTime = timeManager.getCurrentTime().toString();
  String smokeNotificationTime = startTime;
  String calibrationNotificationTime = startTime;
  String heatNotificationTime = startTime;
  String coolNotificationTime = startTime;
  String humidityNotificationTime = startTime;

public:
  NotificationPolicy()
  {
  }

  bool notifyOfSmoke(const Measurement &measurement)
  {
    if (measurement.getSensor() == SensorType::MQ135 && (timeManager.isTimeInRange(TIME_START_SMOKE_DETECTION, TIME_END_SMOKE_DETECTION) && measurement.getCorrectedPPM() > s_cppmThreshold && isNotifySmoke) || isAlwaysNotifySmoke)
    {
      if (s_notificationRate * 60 <= timeManager.getSecondsPassed(smokeNotificationTime))
      {
        smokeNotificationTime = timeManager.getCurrentTime().toString();
        return true;
      }
    }
    return false;
  }

  bool notifyOfCalibration(const Measurement &measurement)
  {
    if (measurement.getSensor() == SensorType::MQ135 && timeManager.isTimeInRange(s_startCalibration, s_endCalibration) && measurement.getRZero() > THRESHOLD_LOWER_CALIBRATION && measurement.getRZero() < THRESHOLD_UPPER_CALIBRATION && s_isGasSensorCalibration)
    {
      if (s_notificationRate * 60 <= timeManager.getSecondsPassed(calibrationNotificationTime))
      {
        calibrationNotificationTime = timeManager.getCurrentTime().toString();
        return true;
      }
    }
    return false;
  }

  bool notifyOfHeat(const Measurement &measurement)
  {
    if (measurement.getSensor() == SensorType::DHT && !isHeatNotificationSent && measurement.readTemperature() > s_hotTempThershold && measurement.readTemperature() != 0 && isNotifyHygro)
    {
      if (s_notificationRate * 60 <= timeManager.getSecondsPassed(heatNotificationTime))
      {
        heatNotificationTime = timeManager.getCurrentTime().toString();
        isHeatNotificationSent = true;
        return true;
      }
    }
    else if (isHeatNotificationSent && measurement.readTemperature() < s_hotTempThershold && measurement.readTemperature() != 0)
    {
      isHeatNotificationSent = false;
    }
    return false;
  }
  bool notifyOfCool(const Measurement &measurement)
  {
    if (measurement.getSensor() == SensorType::DHT && !isCoolNotificationSent && measurement.readTemperature() < s_coolTempThershold && isNotifyHygro && measurement.readTemperature() != 0)
    {
      if (s_notificationRate * 60 <= timeManager.getSecondsPassed(coolNotificationTime))
      {
        coolNotificationTime = timeManager.getCurrentTime().toString();
        isCoolNotificationSent = true;
        return true;
      }
    }
    else if (isCoolNotificationSent && measurement.readTemperature() > s_coolTempThershold && measurement.readTemperature() != 0)
    {
      isCoolNotificationSent = false;
    }
    return false;
  }
  bool notifyOfHumidity(const Measurement &measurement)
  {
    if ((measurement.getSensor() == SensorType::DHT && !isWetNotificationSent && measurement.readHumidity() > s_humidThershold && isNotifyHygro && measurement.readHumidity() != 0) || isAlwaysNotifyHygro)
    {
      if (s_notificationRate * 60 <= timeManager.getSecondsPassed(humidityNotificationTime))
      {
        humidityNotificationTime = timeManager.getCurrentTime().toString();
        isWetNotificationSent = true;
        return true;
      }
      return false;
    }
    else if (((measurement.readHumidity() < s_humidThershold || measurement.readHumidity() < s_dryThershold) && isWetNotificationSent && isNotifyHygro && measurement.readHumidity() != 0) || isAlwaysNotifyHygro)
    {
      isWetNotificationSent = false;
      return true;
    }
    return false;
  }
};

#endif
