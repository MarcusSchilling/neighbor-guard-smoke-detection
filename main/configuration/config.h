#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <variant>

std::map<std::string, std::variant<int,double,bool>> configList;

int s_cppmThreshold = 510; // [PPM] corrected
int s_hotTempThershold = 28; // [°C]
int s_coolTempThershold = 10; // [°C]
int s_humidThershold = 60; // [%]
int s_dryThershold = 40; // [%]
bool s_isGasSensorCalibration = false; // set to true to calibrate between @s_startCalibration and @s_endCalibration
int s_startCalibration = 5; // [HH]
int s_endCalibration = 5; // [HH]
double s_rZeroCalibration = 619.5; // [Ohm] Gas sensor calibration rZero  !!TODO!! change to double in rzero_calibration_handler.cpp !!TODO!!
double s_updateRate = 0.25; // [Hz] 1Hz=1s delay; 2Hz=>500ms;
// Telegram notification policy
// 0: Mute --> send no notifications
// 1: Normal (default) --> notifiy when threshold policy met @s_notificationRate
// 2: Smoke only --> notify only of gas sensor readings when threshold policy met @s_notificationRate
// 3: Hygrometer only --> notify only of hygrometer readings when threshold policy met @s_notificationRate
// 11: Debug --> notify of every sensor reading @s_updateRate
// 12: Debug Gas Sensor --> notify of every gas sensor reading @s_updateRate
// 13: Debug Hygrometer --> notify of every hygrometer reading at @s_updateRate
int s_notificationState = 1;
double s_notificationRate = 5.0; // [Min] Telegram notification rate

// Dictionary of configuration variable for /return-vaariable message reply
void initConfigList() {
    configList["cppm"] = s_cppmThreshold;
    configList["hot"] = s_hotTempThershold;
    configList["cool"] = s_coolTempThershold;
    configList["humid"] = s_humidThershold;
    configList["dry"] = s_dryThershold;
    configList["isCal"] = s_isGasSensorCalibration;
    configList["startCal"] = s_startCalibration;
    configList["endCal"] = s_endCalibration;
    configList["rZero"] = s_rZeroCalibration;
    configList["updateRate"] = s_updateRate;
    configList["notifState"] = s_notificationState;
    configList["notifRate"] = s_notificationRate;
}

#endif