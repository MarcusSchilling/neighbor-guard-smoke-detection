# Overview of the possible telegram dynamic configuration options

Command | Usage | Function | Variable update | Unit
-------- | -------- | -------- | -------- | --------
`smoke-threshold` | /smoke-threshold 600   | Change the notification policy threshold for smoke detection warning.   | `s_cppmThreshold` | PPM
`hot-threshold` | /hot-threshold 28   | Change the notification policy threshold for heat detection warning.  | `s_hotTempThershold` | °C
`cool-threshold` | /cool-threshold 22   | Change the notification policy threshold for cold detection warning.  | `s_coolTempThershold` | °C
`humid-threshold` | /humid-threshold 60   | Change the notification policy threshold for humidity detection warning.  | `s_humidThershold` | %
`dry-threshold` | /dry-threshold 40   | Change the notification policy threshold for dry air detection warning.  | `s_dryThershold` | %
`is-calibration` | /is-calibration 0   | Change whether to perform gas sensor calibration between <br /> @`s_start_calibration` and @`s_end_calibration` or not to calibrate. | `s_isGasSensorCalibration` | _bool_
`start-calibration` | /start-calibration 5   | Change the start time for gas sensor calibration. | `s_startCalibration` | Hour
`end-calibration` | /end-calibration 5   | Change the end time for gas sensor calibration. <br /> Set to @`s_start_calibration` for 1 hour calibration window. | `s_endCalibration` | Hour
`rzero` | /rzero 619.5   | Change the rZero value for gas sensor calibration. | `s_rZeroCalibration` | Ohm
`update-rate` | /update-rate 2   | Change the delay for the microcontroller / rate at which the sensor reading is updated. | `s_updateRate` | Hz
`notification-state` | /notification-state 1  | Change the notification state. <br /> 0: **Mute** --> send no notifications <br /> 1: **Normal** (default) --> notifiy when threshold policy met @`s_notificationRate` <br /> 2: **Smoke only** --> notify only of gas sensor readings when threshold policy met @`s_notificationRate` <br /> 3: **Hygrometer only** --> notify only of hygrometer readings when threshold policy met @`s_notificationRate` <br /> 11: **Debug** --> notify of every sensor reading @`s_updateRate` <br /> 12: **Debug Gas Sensor** --> notify of every gas sensor reading @`s_updateRate` <br /> 13: **Debug Hygrometer** --> notify of every hygrometer reading at @`s_updateRate` | `s_notificationState` | _int_
`notification-rate` | /notification-rate 30   | Change the rate at which a notification is sent via telegram. | `s_notificationRate` | Minutes
`get` | /get cppm   | Return the configuration variable value via telegram. <br /> cppm: `s_cppmThreshold` <br /> hot: `s_hotTempThershold` <br /> cool: `s_coolTempThershold` <br /> humid: `s_humidThershold` <br /> dry: `s_dryThershold` <br /> isCal: `s_isGasSensorCalibration` <br /> startCal: `s_startCalibration` <br /> endCal: `s_endCalibration` <br /> rZero: `s_rZeroCalibration` <br /> updateRate: `s_updateRate` <br /> notifState: `s_notificationState` <br /> notifRate: `s_notificationRate`| - | -
`restart` | /restart  | Restart the ESP microcontroller. This also resets the configuration.  | - | -