#ifndef HOT_THRESHOLD_HANDLER_CPP
#define HOT_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./cool_threshold_handler.cpp"
class HotThresholdHandler : public Handler
{
public:
    HotThresholdHandler() : Handler("/hot-threshold", nullptr){};

    void execute(FB_msg &msg)
    {
        s_hotTempThershold = msg.text.substring(14).toInt();
        telegramBot.sendMessage("Heat warning detection threshold set to: " + msg.text.substring(14) + "°C");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        CoolThresholdHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif