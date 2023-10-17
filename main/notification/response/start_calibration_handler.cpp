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
    StartCalibrationHandler() : Handler("/start-calibration", nullptr){};

    void execute(FB_msg &msg)
    {
        s_startCalibration = msg.text.substring(18).toInt();
        telegramBot.sendMessage("Calibration start time set to: " + msg.text.substring(18));
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        EndCalibrationHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif