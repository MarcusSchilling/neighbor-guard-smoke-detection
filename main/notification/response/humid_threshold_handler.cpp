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
    HumidThresholdHandler() : Handler("/humid-threshold", nullptr){};

    void execute(FB_msg &msg)
    {
        s_humidThershold = msg.text.substring(16).toInt();
        telegramBot.sendMessage("Humid detection threshold set to: " + msg.text.substring(16) + "%");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        DryThresholdHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif