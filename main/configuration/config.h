#ifndef CONFIG_H
#define CONFIG_H

int s_cppmThreshold = 600; // [PPM] corrected
int s_hotTempThershold = 28; // [°C]
int s_coolTempThershold = 22; // [°C]
int s_humidThershold = 60; // [%]
int s_dryThershold = 40; // [%]
bool s_isGasSensorCalibration = false; // set to true to calibrate between @s_startCalibration and @s_endCalibration
int s_startCalibration = 5; // [HH]
int s_endCalibration = 5; // [HH]
int s_rZeroCcalibration = 620; // [Ohm] Gas sensor calibration rZero  !!TODO!! change to double in rzero_calibration_handler.cpp !!TODO!!
int s_updateRate = 2; // [Hz] 1Hz=1s delay; 2Hz=>500ms;
// Telegram notification policy
// 0: Mute --> send no notifications
// 1: Normal (default) --> notifiy when threshold policy met @s_notificationRate
// 2: Smoke only --> notify only of gas sensor readings when threshold policy met @s_notificationRate
// 3: Hygrometer only --> notify only of hygrometer readings when threshold policy met @s_notificationRate
// 11: Debug --> notify of every sensor reading @s_updateRate
// 12: Debug Gas Sensor --> notify of every gas sensor reading @s_updateRate
// 13: Debug Hygrometer --> notify of every hygrometer reading at @s_updateRate
int s_notificationState = 1;
int s_notificationRate = 5; // [Min] Telegram notification rate

#endif