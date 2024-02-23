#ifndef TIME_MANAGER_CPP
#define TIME_MANAGER_CPP

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <FastBot.h>

class Duration
{
    int seconds;

public:
    Duration(int seconds) : seconds(seconds){};
};

class Time
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time(int hours, int minutes, int seconds) : hours(hours), minutes(minutes), seconds(seconds){};

    Time(unsigned long epoch, int8_t timezone = 2)
    {
        FB_Time messageTime{epoch, timezone};
        hours = messageTime.hour;
        minutes = messageTime.minute;
        seconds = messageTime.second;
    }

    Duration operator-(const Time &other)
    {
        return Duration((other.seconds - this->seconds) + ((other.minutes - this->minutes) * 60) + ((other.hours - this->hours) * 60 * 60));
    }

    String toString() const
    {
        char buffer[9];
        sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
        return String(buffer);
    }

    bool operator>(const Time &other)
    {
        int totalSecondsThis = this->hours * 60 * 60 + this->minutes * 60 + this->seconds;
        int totalSecondsOther = other.hours * 60 * 60 + other.minutes * 60 + other.seconds;
        return totalSecondsThis > totalSecondsOther;
    }
};
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

    Time getCurrentTime()
    {
        timeClient.update();
        return Time{timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds()};
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