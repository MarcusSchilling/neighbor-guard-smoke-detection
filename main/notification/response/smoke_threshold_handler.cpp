#ifndef SMOKE_THRESHOLD_HANDLER_CPP
#define SMOKE_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./hot_threshold_handler.cpp"
class SmokeThresholdHandler : public Handler
{
public:
    SmokeThresholdHandler() : Handler("/smoke-threshold", nullptr){};

    void execute(FB_msg &msg)
    {
        s_cppmThreshold = msg.text.substring(16).toInt();
        telegramBot.sendMessage("Smoke detection threshold set to: " + msg.text.substring(16) + "PPM");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        HotThresholdHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif