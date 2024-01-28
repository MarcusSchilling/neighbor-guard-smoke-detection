#ifndef COOL_THRESHOLD_HANDLER_CPP
#define COOL_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./humid_threshold_handler.cpp"
class CoolThresholdHandler : public Handler
{

public:
    CoolThresholdHandler() : Handler("/coolThreshold ((|[+-])[1-9][0-9]*)", new HumidThresholdHandler()){};

    void execute(FB_msg &msg)
    {
        s_coolTempThershold = parseRegex(msg.text, 1).toInt();
        telegramBot.sendMessage("Cooldown detection threshold set to: " + String(s_coolTempThershold) + " °C");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif