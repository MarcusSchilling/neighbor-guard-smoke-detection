#ifndef RZERO_CALIBRATION_HANDLER_CPP
#define RZERO_CALIBRATION_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./update_rate_handler.cpp"
class RZeroCalibrationHandler : public Handler
{

public:
    RZeroCalibrationHandler() : Handler("/rzero", new UpdateRateHandler()){};

    void execute(FB_msg &msg)
    {
        s_rZeroCalibration = msg.text.substring(getRegexLength()).toDouble();
        telegramBot.sendMessage("Calibration rZero set to: " + msg.text.substring(getRegexLength()) + " Ohm");
        telegramBot.deleteMessage(msg.messageID);
        ESP.restart();
    }
};

#endif