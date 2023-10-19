#ifndef IS_CALIBRATION_HANDLER_CPP
#define IS_CALIBRATION_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./start_calibration_handler.cpp"
class IsCalibrationHandler : public Handler
{

public:
    IsCalibrationHandler() : Handler("/is-calibration", new StartCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_isGasSensorCalibration = msg.text.substring(getRegexLength()).toInt();
        telegramBot.sendMessage("Calibration set to: " + msg.text.substring(getRegexLength()));
    }
};

#endif