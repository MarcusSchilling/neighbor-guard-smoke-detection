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
    SmokeThresholdHandler() : Handler("/smoke-threshold", new HotThresholdHandler()){};

    void execute(FB_msg &msg)
    {
        s_cppmThreshold = msg.text.substring(getRegexLength()).toInt();
        Serial.println("Smoke handling message: " + msg.text);
        telegramBot.sendMessage("Smoke detection threshold set to: " + msg.text.substring(getRegexLength()) + " PPM");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif