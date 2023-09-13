// -------------- Notification Policy --------------

// Smoke Detection
#define TIME_START_SMOKE_DETECTION 7
#define TIME_END_SMOKE_DETECTION 24
#define THRESHOLD_PPM 300.0         // ppm
#define isConstantMQ135Notify false // if true always notify of values

// Safe to air out room
#define THRESHOLD_COOL 22.0 // °C
#define THRESHOLD_HUM 60.0  // %

// Heat Warning
#define THRESHOLD_HEAT 28.0 // °C

// Sensor Calibration
#define TIME_START_CALIBRATION 5
#define TIME_END_CALIBRATION 5
#define THRESHOLD_LOWER_CALIBRATION 0.0   // Ohm
#define THRESHOLD_UPPER_CALIBRATION 700.0 // Ohm

// -------------- Sensors --------------

// MQ135
#include <MQ135.h>
#define ANALOGPIN 0
#define RZEROCALIBRATION 510 // Ohm
#define DEFAULT_TEMP 22.0    // °c
#define DEFAULT_HUM 30.0     // %

// DHT11
#include <DHT.h>
#define DIGITALPIN D2
#define DHTTYPE DHT11 // DHT11 or DHT22, depends on your sensor
#define isUseHygro true
#define isCalibrateSensor true

// -------------- System --------------
#define DELAYTIME 15000
#define BUADRATE 115200