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
    RZeroCalibrationHandler() : Handler("/rzero ([1-9]*\\.[0-9]*|[0-9]*)", new UpdateRateHandler()){};

    void execute(FB_msg &msg)
    {
        s_rZeroCalibration = std::stod(parseRegex(msg.text.c_str(), 1));
        telegramBot.sendMessage("Calibration rZero set to: " + String(s_rZeroCalibration, 2) + " Ohm");
        telegramBot.deleteMessage(msg.messageID);
        ESP.restart();
    }
};

#endif