#ifndef END_CALIBRATION_HANDLER_CPP
#define END_CALIBRATION_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./rzero_calibration_handler.cpp"
class EndCalibrationHandler : public Handler
{

public:
    EndCalibrationHandler() : Handler("/endCalibration ([1-9]|1[0-9]|2[0-4])\b", new RZeroCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_endCalibration = std::stoi(parseRegex(msg.text.c_str(), 1));
        telegramBot.sendMessage("Calibration end time set to: " + String(s_endCalibration));
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif