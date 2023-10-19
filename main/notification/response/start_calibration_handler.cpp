#ifndef START_CALIBRATION_HANDLER_CPP
#define START_CALIBRATION_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./end_calibration_handler.cpp"
class StartCalibrationHandler : public Handler
{

public:
    StartCalibrationHandler() : Handler("/start-calibration", new EndCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_startCalibration = msg.text.substring(getRegexLength()).toInt();
        telegramBot.sendMessage("Calibration start time set to: " + msg.text.substring(getRegexLength()));
    }
};

#endif