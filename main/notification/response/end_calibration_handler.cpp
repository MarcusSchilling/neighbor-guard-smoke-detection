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
    EndCalibrationHandler() : Handler("/end-calibration", nullptr){};

    void execute(FB_msg &msg)
    {
        s_endCalibration = msg.text.substring(16).toInt();
        telegramBot.sendMessage("Calibration end time set to: " + msg.text.substring(16));
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        RZeroCalibrationHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif