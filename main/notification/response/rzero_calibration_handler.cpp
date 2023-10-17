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
    RZeroCalibrationHandler() : Handler("/rzero", nullptr){};

    void execute(FB_msg &msg)
    {
        s_rZeroCcalibration = msg.text.substring(6).toInt();
        telegramBot.sendMessage("Calibration rZero set to: " + msg.text.substring(6) + " Ohm");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        UpdateRateHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif