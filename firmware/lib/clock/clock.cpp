#include "clock.h"

void Clock::setup()
{
    timeClient.begin();
}

void Clock::tasks()
{
    timeClient.update();
}

String Clock::getTimeString()
{
    timeClient.setTimeOffset(isSummerTime() ? 7200 : 3600);
    return timeClient.getFormattedTime().substring(0, 5);
}

bool Clock::isSummerTime()
{
    time_t now = timeClient.getEpochTime();
    struct tm *timeinfo;
    timeinfo = localtime(&now);
    return timeinfo->tm_isdst;
}

bool Clock::currentTimeInRange(String start, String end)
{
    String now = getTimeString();
    now.replace(":", "");
    start.replace(":", "");
    end.replace(":", "");

    int nowInt = now.toInt();
    int startInt = start.toInt();
    int endInt = end.toInt();

    if (startInt <= endInt)
    {
        return nowInt >= startInt && nowInt <= endInt;
    }

    return nowInt >= startInt || nowInt <= endInt;
}