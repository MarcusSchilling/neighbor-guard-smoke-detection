# Overview of the possible telegram dynamic configuration options

Chain Link |Command | Usage | Function | Variable update | Unit
-------- | -------- | -------- | -------- | -------- | --------
1 | `smoke-threshold` | /smoke-threshold 600   | Change the notification policy threshold for smoke detection warning.   | `s_cppmThreshold` | PPM
2 | `hot-threshold` | /hot-threshold 28   | Change the notification policy threshold for heat detection warning.  | `s_hotTempThershold` | °C
3 | `cool-threshold` | /cool-threshold 22   | Change the notification policy threshold for cold detection warning.  | `s_coolTempThershold` | °C
4 | `humid-threshold` | /humid-threshold 60   | Change the notification policy threshold for humidity detection warning.  | `s_humidThershold` | %
5 | `dry-threshold` | /dry-threshold 40   | Change the notification policy threshold for dry air detection warning.  | `s_dryThershold` | %
6 | `is-calibration` | /is-calibration 0   | Change whether to perform gas sensor calibration between <br /> @`s_start_calibration` and @`s_end_calibration` or not to calibrate. | `s_isGasSensorCalibration` | _bool_
7 | `start-calibration` | /start-calibration 5   | Change the start time for gas sensor calibration. | `s_startCalibration` | Hour
8 | `end-calibration` | /end-calibration 5   | Change the end time for gas sensor calibration. <br /> Set to @`s_start_calibration` for 1 hour calibration window. | `s_endCalibration` | Hour
9 | `rzero` | /rzero 619.5   | Change the rZero value for gas sensor calibration. | `s_rZeroCalibration` | Ohm
10 | `update-rate` | /update-rate 2   | Change the delay for the microcontroller / rate at which the sensor reading is updated. | `s_updateRate` | Hz
11 | `notification-state` | /notification-state 1  | Change the notification state. <br /> 0: **Mute** --> send no notifications <br /> 1: **Normal** (default) --> notifiy when threshold policy met @`s_notificationRate` <br /> 2: **Smoke only** --> notify only of gas sensor readings when threshold policy met @`s_notificationRate` <br /> 3: **Hygrometer only** --> notify only of hygrometer readings when threshold policy met @`s_notificationRate` <br /> 11: **Debug** --> notify of every sensor reading @`s_updateRate` <br /> 12: **Debug Gas Sensor** --> notify of every gas sensor reading @`s_updateRate` <br /> 13: **Debug Hygrometer** --> notify of every hygrometer reading at @`s_updateRate` | `s_notificationState` | _int_
12 | `notification-rate` | /notification-rate 30   | Change the rate at which a notification is sent via telegram. | `s_notificationRate` | Minutes
13 | `get` | /get cppm   | Return the configuration variable value via telegram. <br /> cppm: `s_cppmThreshold` <br /> hot: `s_hotTempThershold` <br /> cool: `s_coolTempThershold` <br /> humid: `s_humidThershold` <br /> dry: `s_dryThershold` <br /> isCal: `s_isGasSensorCalibration` <br /> startCal: `s_startCalibration` <br /> endCal: `s_endCalibration` <br /> rZero: `s_rZeroCalibration` <br /> updateRate: `s_updateRate` <br /> notifState: `s_notificationState` <br /> notifRate: `s_notificationRate`| - | -
14 | `restart` | /restart  | Restart the ESP microcontroller. This also resets the configuration.  | - | -