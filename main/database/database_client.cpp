#ifndef DATABASE_CLIENT_CPP
#define DATABASE_CLIENT_CPP

#include "../configuration/shared.credentials.h"
#include "../configuration/constants.h"
#include "../configuration/config.h"
#include "../domain/measurement.hpp"

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "database_client.hpp"

InfluxDBClient influx{INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET_NAME, INFLUXDB_TOKEN, InfluxDbCloud2CACert};

TimeSeriesDatabase::TimeSeriesDatabase()
{
}

bool TimeSeriesDatabase::bucketExists(const String &bucketName, const String &namespaceName)
{
    BucketsClient buckets = influx.getBucketsClient();
    if (buckets.checkBucketExists((namespaceName + bucketName).c_str()))
    {
        Serial.println("Bucket " + namespaceName + bucketName + " already exists");
        Bucket b = buckets.findBucket((namespaceName + bucketName).c_str());
        return true; // Bucket exists
    }
    else
    {
        return false; // Bucket does not exist
    }
}

bool TimeSeriesDatabase::createBucket(const String &bucketName, const String &namespaceName, uint32_t &retention)
{
    BucketsClient buckets = influx.getBucketsClient();
    Bucket b = buckets.createBucket((namespaceName + bucketName).c_str(), retention);
    if (!b)
    {
        Serial.print("Bucket creating error: ");
        Serial.println(buckets.getLastErrorMessage());
        return false;
    }
    Serial.print("Created bucket: ");
    Serial.println(b.toString());
    return true;
}

void TimeSeriesDatabase::initDatabaseConnection()
{
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

    if (influx.validateConnection())
    {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(influx.getServerUrl());

        if (!bucketExists(INFLUXDB_BUCKET, NAMESPACE))
        {
            if (createBucket(INFLUXDB_BUCKET, NAMESPACE, s_influxBucketRetention))
            {
                Serial.println("InfluxDB bucket created successfully.");
            }
            else
            {
                Serial.println("Failed to create InfluxDB bucket.");
            }
        }
        else
        {
            Serial.println("InfluxDB bucket already exists.");
        }
    }
    else
    {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(influx.getLastErrorMessage());
    }
}

void TimeSeriesDatabase::write(const Measurement &measurement)
{
    Point sensor{"air-quality"};
    if (measurement.getSensor() == SensorType::mq135)
    {
        sensor.addTag("sensor_type", "MQ135");
        sensor.addField("R-Zero", measurement.getRZero());
        sensor.addField("corrected R-Zero", measurement.getCorrectedRZero());
        sensor.addField("ppm", measurement.getPPM());
        sensor.addField("corrected ppm", measurement.getCorrectedPPM());
        sensor.addField("resistance", measurement.getResistance());
        int smoke = (measurement.getCorrectedPPM() > s_cppmThreshold) ? 1 : 0;
        sensor.addField("smoke-detected", smoke * s_cppmThreshold / 2);
        sensor.addField("smoke-threshold", s_cppmThreshold);
        if (s_cleanAirLabel)
        {
            sensor.addField("smoke-label", s_cleanAirLabel ? s_cppmThreshold * -0.5 : 0);
        }
        else
        {
            sensor.addField("smoke-label", s_smokeLabel ? s_cppmThreshold * 0.5 : 0);
        }
        s_smokeLabel = false;
        s_cleanAirLabel = false;
    }
    else if (measurement.getSensor() == SensorType::dht)
    {
        sensor.addTag("sensor_type", "DHT11");
        sensor.addField("temperature", measurement.readTemperature());
        sensor.addField("humidity", measurement.readHumidity());
    }
    else
    {
        Serial.print("Sensor not yet configured for influxDB logging");
    }

    if (influx.writePoint(sensor))
    {
        Serial.println("Data written to InfluxDB");
    }
    else
    {
        Serial.print("InfluxDB write failed: ");
        Serial.println(influx.getLastErrorMessage());
    }
}
#endif