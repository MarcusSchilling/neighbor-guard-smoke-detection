#ifndef NOTIFICATION_POLICY
#define NOTIFICATION_POLICY

#include "measurement.hpp"
#include <WiFiUdp.h>
#include <NTPClient.h>

class NotificationPolicy
{
private:
    WiFiUDP udp;
    // NTP settings
    const char *ntpServer = "pool.ntp.org";
    NTPClient timeClient = NTPClient(udp, ntpServer);

public:
    NotificationPolicy()
    {
        timeClient.begin();
        // Set the offset for Central European Summer Time (CEST).
        timeClient.setTimeOffset(7200); // 7200 seconds correspond to 2 hours offset to GMT
    }

    bool isTimeInRange(int startHour, int endHour)
    {
        timeClient.update();
        int currentHour = timeClient.getHours();
        return (currentHour >= startHour && currentHour <= endHour);
    }

    bool shouldNotify(const Measurement &measurement)
    {
        return isTimeInRange(9, 23) && measurement.getPM() > 10;
    }
};

#endif