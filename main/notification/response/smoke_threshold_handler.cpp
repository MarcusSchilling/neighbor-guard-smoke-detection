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
    SmokeThresholdHandler() : Handler("/smokeThreshold ([1-9][0-9]*)", new HotThresholdHandler()){}; // HOT

    void execute(FB_msg &msg)
    {
        s_cppmThreshold = parseRegex(msg.text, 1).toInt();
        telegramBot.sendMessage("Smoke detection threshold set to: " + String(s_cppmThreshold) + " PPM");
    }
};

#endif