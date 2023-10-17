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
    CoolThresholdHandler() : Handler("/cool-threshold", nullptr){};

    void execute(FB_msg &msg)
    {
        s_coolTempThershold = msg.text.substring(15).toInt();
        telegramBot.sendMessage("Cooldown detection threshold set to: " + msg.text.substring(15) + "°C");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        HumidThresholdHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif