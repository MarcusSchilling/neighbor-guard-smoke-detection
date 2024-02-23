// -------------- Notification Policy --------------

// Smoke Detection
#define TIME_START_SMOKE_DETECTION 7
#define TIME_END_SMOKE_DETECTION 24
#define THRESHOLD_PPM 300.0 // ppm

// Sensor Calibration
#define THRESHOLD_LOWER_CALIBRATION 0.0   // Ohm
#define THRESHOLD_UPPER_CALIBRATION 700.0 // Ohm

// -------------- Sensors --------------

// MQ135
#include <MQ135.h>
#define ANALOGPIN 0
#define DEFAULT_TEMP 22.0 // °c
#define DEFAULT_HUM 30.0  // %

// DHT11
#include <DHT.h>
#define DIGITALPIN D2
#define DHTTYPE DHT22 // DHT11 or DHT22, depends on your sensor
#define isUseHygro true

// -------------- System --------------
#define BUADRATE 115200
// Time zone info
#define TZ_INFO "UTC1"