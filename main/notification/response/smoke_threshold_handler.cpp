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
    SmokeThresholdHandler() : Handler("/smokeThreshold ([1-9][0-9]*)", new HotThresholdHandler()){};

    void execute(FB_msg &msg)
    {
        s_cppmThreshold = std::stoi(parseRegex(msg.text.c_str(), 1));
        telegramBot.sendMessage("Smoke detection threshold set to: " +  String(s_cppmThreshold)  + " PPM");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif