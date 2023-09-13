#ifndef SMOKE_THRESHOLD_HANDLER_CPP
#define SMOKE_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
class SmokeThresholdHandler : public Handler
{
public:
    SmokeThresholdHandler() : Handler("/smoke-threshold", nullptr){};

    void execute(FB_msg &msg)
    {
        s_cppmThreshold = msg.text.substring(16).toInt();
        telegramBot.sendMessage("Threshold Detection set to: " + msg.text.substring(16));
    }
};

#endif