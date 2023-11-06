#ifndef DATA_LOGGER_HPP
#define DATA_LOGGER_HPP

#include "observer.cpp"
#include "../domain/measurement.hpp"
#include "../database/database_client.hpp"

class DataLogger : public Observer
{
public:
    TimeSeriesDatabase timeSeriesDatabase;

    DataLogger();

    void update(const Measurement &measurement) override;
};

#endif
