#ifndef MESSAGE_REPLY_CPP
#define MESSAGE_REPLY_CPP

#include "../configuration/credentials.h"
#include "response/smoke_threshold_handler.cpp"

#include <FastBot.h>
FastBot fastBot{BOT_TOKEN};

void newMsg(FB_msg &msg)
{
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