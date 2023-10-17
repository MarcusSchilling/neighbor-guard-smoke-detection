#ifndef DRY_THRESHOLD_HANDLER_CPP
#define DRY_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./is_calibration_handler.cpp"
class DryThresholdHandler : public Handler
{
public:
    DryThresholdHandler() : Handler("/dry-threshold", nullptr){};

    void execute(FB_msg &msg)
    {
        s_dryThershold = msg.text.substring(14).toInt();
        telegramBot.sendMessage("Dry detection threshold set to: " + msg.text.substring(14) + "%");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        IsCalibrationHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif