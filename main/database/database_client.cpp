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
// Method to check if a bucket exists
bool TimeSeriesDatabase::bucketExists(const String &bucketName, const String &namespaceName)
{
    // Get dedicated client for buckets management
    BucketsClient buckets = influx.getBucketsClient();
    // Verify bucket does not exist
    if(buckets.checkBucketExists((namespaceName + bucketName).c_str())) {
        Serial.println("Bucket " + namespaceName + bucketName + " already exists");
        // get reference
        Bucket b = buckets.findBucket((namespaceName + bucketName).c_str());
        return true; // Bucket exists

        // // Delete bucket
        // buckets.deleteBucket(b.getID());
    }
    else
    {
        return false; // Bucket does not exist
    }
}

// Method to create a new bucket
bool TimeSeriesDatabase::createBucket(const String &bucketName, const String &namespaceName, uint32_t &retention)
{
    // Get dedicated client for buckets management
    BucketsClient buckets = influx.getBucketsClient();
    Bucket b = buckets.createBucket((namespaceName + bucketName).c_str(), retention);
    if(!b) {
        // some error occurred
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

    // Check server connection
    if (influx.validateConnection())
    {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(influx.getServerUrl());

        // Check if the bucket exists, if not, create it
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

// Methode zum Speichern der Sensorwerte
void TimeSeriesDatabase::write(const Measurement &measurement)
{
    Point sensor{"air-quality"};
    if (measurement.getSensor() == SensorType::MQ135)
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
    else if (measurement.getSensor() == SensorType::DHT)
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
    // Serial.println("Waiting 1 second");
    // delay(1000/s_updateRate);
}
#endif