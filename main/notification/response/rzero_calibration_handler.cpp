#ifndef RZERO_CALIBRATION_HANDLER_CPP
#define RZERO_CALIBRATION_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "../../configuration/constants.h"
#include "./update_rate_handler.cpp"

class RZeroCalibrationHandler : public Handler
{

public:
    RZeroCalibrationHandler() : Handler("/rzero ([1-9]*\\.[0-9]*|[0-9]*)", new UpdateRateHandler()){};

    void execute(FB_msg &msg)
    {
        s_rZeroCalibration = parseRegex(msg.text, 1).toDouble();
        telegramBot.sendMessage("Calibration rZero set to: " + String(s_rZeroCalibration, 2) + " Ohm");
        gasSensor = MQ135(ANALOGPIN, s_rZeroCalibration);
        // telegramBot.sendMessage("Restarting Controller");
        // ESP.restart();
    }
};

#endif