#ifndef MESSAGE_REPLY_CPP
#define MESSAGE_REPLY_CPP

#include "../configuration/shared.credentials.h"
#include "response/smoke_threshold_handler.cpp"

#include <FastBot.h>
FastBot fastBot{BOT_TOKEN};
int32_t lastReadMessageId = 0;
Time *startupTime = nullptr;
TimeManager timeManager{};

void newMsg(FB_msg &msg)
{
    if (!startupTime)
    {
        startupTime = new Time{timeManager.getCurrentTime()};
    }
    Time messageTime{msg.unix};
    bool wasMessageSendAfterSensorStartup = messageTime > *startupTime;
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