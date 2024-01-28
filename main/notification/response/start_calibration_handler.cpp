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
    StartCalibrationHandler() : Handler("/startCalibration ([1-9]|1[0-9]|2[0-4])\b", new EndCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_startCalibration = parseRegex(msg.text, 1).toInt();
        telegramBot.sendMessage("Calibration start time set to: " + String(s_startCalibration));
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif