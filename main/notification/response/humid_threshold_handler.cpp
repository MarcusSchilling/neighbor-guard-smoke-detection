#ifndef HUMID_THRESHOLD_HANDLER_CPP
#define HUMID_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./dry_threshold_handler.cpp"
class HumidThresholdHandler : public Handler
{

public:
    HumidThresholdHandler() : Handler("/humid-threshold", new DryThresholdHandler()){};

    void execute(FB_msg &msg)
    {
        s_humidThershold = msg.text.substring(getRegexLength()).toInt();
        telegramBot.sendMessage("Humid detection threshold set to: " + msg.text.substring(getRegexLength()) + " %");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif