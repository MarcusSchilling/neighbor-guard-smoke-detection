#ifndef TIME_MANAGER_CPP
#define TIME_MANAGER_CPP

#include <WiFiUdp.h>
#include <NTPClient.h>

class TimeManager
{
private:
    WiFiUDP udp;
    // NTP settings
    const char *ntpServer = "pool.ntp.org";
    NTPClient timeClient = NTPClient(udp, ntpServer);
    String startTime;

public:
    TimeManager()
    {
        timeClient.begin();
        // Set the offset for Central European Summer Time (CEST).
        timeClient.setTimeOffset(7200); // 7200 seconds correspond to 2 hours offset to GMT
        startTime = getCurrentTime();
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

    String getCurrentTime()
    {
        char buffer[9];
        sprintf(buffer, "%02d:%02d:%02d", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
        return String(buffer);
    }

    int getSecondsPassed(String startTime)
    {
        // Convert start time string to datetime object
        struct tm tm;
        strptime(startTime.c_str(), "%H:%M:%S", &tm);
        time_t startTimeEpoch = mktime(&tm);

        // Get current epoch time
        time_t currentTimeEpoch = getEpochTime();

        // Calculate difference in seconds
        int secondsPassed = difftime(currentTimeEpoch, startTimeEpoch);

        return secondsPassed;
    }
};

#endif