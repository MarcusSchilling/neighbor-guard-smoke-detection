#ifndef DATABASE_CLIENT_HPP
#define DATABASE_CLIENT_HPP

#include <string>

class TimeSeriesDatabase
{
public:
    TimeSeriesDatabase();
    void initDatabaseConnection();
    void write(const Measurement &measurement);
};

#endif