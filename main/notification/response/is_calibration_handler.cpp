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
    IsCalibrationHandler() : Handler("/isCalibration ([01])", new StartCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_isGasSensorCalibration = parseRegex(msg.text, 1).toInt();
        telegramBot.sendMessage("Calibration set to: " + String(s_isGasSensorCalibration));
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif