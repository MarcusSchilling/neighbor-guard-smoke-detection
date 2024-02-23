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
    HumidThresholdHandler() : Handler("/humidThreshold ([1-9][0-9]*)", new DryThresholdHandler()){};

    void execute(FB_msg &msg)
    {
        s_humidThershold = parseRegex(msg.text, 1).toInt();
        telegramBot.sendMessage("Humid detection threshold set to: " + String(s_humidThershold) + " %");
    }
};

#endif