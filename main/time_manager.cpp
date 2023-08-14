#ifndef TIME_MANAGER
#define TIME_MANAGER

#include <WiFiUdp.h>
#include <NTPClient.h>

class TimeManager
{
private:
    WiFiUDP udp;
    // NTP settings
    const char *ntpServer = "pool.ntp.org";
    NTPClient timeClient = NTPClient(udp, ntpServer);

public:
    TimeManager()
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

    time_t getEpochTime() 
    {
        return timeClient.getEpochTime();
    }

};

#endif