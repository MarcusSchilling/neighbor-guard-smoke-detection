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
    DryThresholdHandler() : Handler("/dry-threshold", new IsCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_dryThershold = msg.text.substring(getRegexLength()).toInt();
        telegramBot.sendMessage("Dry detection threshold set to: " + msg.text.substring(getRegexLength()) + " %");
    }
};

#endif