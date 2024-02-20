#ifndef MESSAGE_REPLY_CPP
#define MESSAGE_REPLY_CPP

#include "../configuration/shared.credentials.h"
#include "response/smoke_threshold_handler.cpp"

#include <FastBot.h>
FastBot fastBot{BOT_TOKEN};
int32_t lastReadMessageId = 0;
void newMsg(FB_msg &msg)
{

    // int16_t timeZoneEurope = 1;
    // FB_Time messageTime{msg.unix, timeZoneEurope};
    // telegramBot.sendMessage(messageTime.dateString());
    if (lastReadMessageId == msg.messageID)
    {
        // message already processed eventually broken
        return;
    }
    else
    {
        lastReadMessageId = msg.messageID;
    }
    SmokeThresholdHandler startHandler;
    startHandler.handleRequest(msg);
}

void setupMessageReply()
{
    fastBot.sendMessage("Startup Completed");
    fastBot.attach(newMsg);
}

void tick()
{
    fastBot.tick();
}

#endif