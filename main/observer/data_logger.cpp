#ifndef DATA_LOGGER_CPP
#define DATA_LOGGER_CPP

#include "data_logger.hpp"
#include "../domain/measurement.hpp"

DataLogger::DataLogger() {
    timeSeriesDatabase.initDatabaseConnection();
}

void DataLogger::update(const Measurement &measurement) {
    timeSeriesDatabase.write(measurement);
}
#endif