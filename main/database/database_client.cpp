#ifndef DATABASE_CLIENT_CPP
#define DATABASE_CLIENT_CPP

#include "../configuration/credentials.h"
#include "../configuration/constants.h"
#include "../configuration/config.h"
#include "../domain/measurement.hpp"

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "database_client.hpp"

InfluxDBClient influx{INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert};

TimeSeriesDatabase::TimeSeriesDatabase()
{
}

// Methode zum Speichern der Sensorwerte
void TimeSeriesDatabase::write(const Measurement &measurement)
{
    Point sensor{"air-quality"};
    if (measurement.getSensor() == SensorType::MQ135) {
        sensor.addTag("sensor_type", "MQ135");
        sensor.addField("R-Zero", measurement.getRZero());
        sensor.addField("corrected R-Zero", measurement.getCorrectedRZero());
        sensor.addField("ppm", measurement.getPPM());
        sensor.addField("corrected ppm", measurement.getCorrectedPPM());
        sensor.addField("resistance", measurement.getResistance());
        int smoke = (measurement.getCorrectedPPM() > s_cppmThreshold) ? 1 : 0;
        sensor.addField("smoke-detected", smoke*1000);
        sensor.addField("smoke-threshold", s_cppmThreshold);
    }
    else if (measurement.getSensor() == SensorType::DHT) {
        sensor.addTag("sensor_type", "DHT11");
        sensor.addField("temperature", measurement.readTemperature());
        sensor.addField("humidity", measurement.readHumidity());
    }
    else {
        Serial.print("Sensor not yet configured for influxDB logging");
    }

    if (influx.writePoint(sensor)) {
        Serial.println("Data written to InfluxDB");
    }
    else {
        Serial.print("InfluxDB write failed: ");
        Serial.println(influx.getLastErrorMessage());
    }
    // Serial.println("Waiting 1 second");
    // delay(1000/s_updateRate);
}

void TimeSeriesDatabase::initDatabaseConnection()
{
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

    // Check server connection
    if (influx.validateConnection()) {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(influx.getServerUrl());
    }
    else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(influx.getLastErrorMessage());
    }
}
#endif