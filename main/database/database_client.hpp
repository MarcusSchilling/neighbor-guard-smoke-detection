#ifndef DATABASE_CLIENT_HPP
#define DATABASE_CLIENT_HPP

#include <string>

class TimeSeriesDatabase
{
public:
    TimeSeriesDatabase();
    bool bucketExists(const String &bucketName, const String &namespaceName);
    bool createBucket(const String &bucketName, const String &namespaceName, uint32_t &retention);
    void initDatabaseConnection();
    void write(const Measurement &measurement);
};

#endif