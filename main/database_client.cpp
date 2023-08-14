#ifndef LOGGER
#define LOGGER
#include "credentials.h"
#include <InfluxDbClient.h>
#include "observer.cpp"
#include "measurement.hpp"
#include "time_manager.cpp"

class TimeSeriesDatabase : public Observer
{

public:
  // Konstruktor
  InfluxDBClient influx{INFLUXDB_HOST, INFLUXDB_ORG, INFLUXDB_DATABASE, INFLUXDB_PORT, INFLUX_DB_TOKEN};
  TimeManager timeManager;
  TimeSeriesDatabase()
  {
  }

  void update(const Measurement &measurement)
  {
    write(measurement.getPM(), measurement.getSensor());
  }

  // Methode zum Speichern der Sensorwerte
  void write(double value, SensorType type)
  {
    Point measurement{"air-quality"};
    measurement.addTag("device", "MQ135");
    measurement.addField("pm2.5", value);
    measurement.addField("gmt_time", timeManager.getEpochTime());
    influx.writePoint(measurement);
  }
};
#endif