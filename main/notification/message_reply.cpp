#ifndef MESSAGE_REPLY_CPP
#define MESSAGE_REPLY_CPP

#include "../configuration/shared.credentials.h"
#include "response/smoke_threshold_handler.cpp"

#include <FastBot.h>

FastBot fastBot{BOT_TOKEN};
int32_t lastReadMessageId = 0;
TimeManager timeManager{};
time_t startupTime = 0;

void newMsg(FB_msg &msg)
{
    if (!startupTime)
    {
        const int startupOffset = 100; // if not used the first message will fail as it is send before the startup time is received here
        startupTime = timeManager.getEpochTime() - startupOffset;
    }
    bool wasMessageSendAfterSensorStartup = msg.unix > startupTime;
    if (wasMessageSendAfterSensorStartup)
    {
        SmokeThresholdHandler startHandler;
        startHandler.handleRequest(msg);
    }
    else
    {
        telegramBot.sendMessage("The Sensor only processes messages sent after startup.");
    }
}

void setupMessageReply()
{
    telegramBot.sendMessage("Startup Completed");
    fastBot.attach(newMsg);
}

void tick()
{
    fastBot.tick();
}

#endif