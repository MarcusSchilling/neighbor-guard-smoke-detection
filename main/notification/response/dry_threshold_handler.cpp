#ifndef DRY_THRESHOLD_HANDLER_CPP
#define DRY_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./is_calibration_handler.cpp"
class DryThresholdHandler : public Handler
{

public:
    DryThresholdHandler() : Handler("/dryThreshold ([1-9][0-9]*)", new IsCalibrationHandler()){};

    void execute(FB_msg &msg)
    {
        s_dryThershold = std::stoi(parseRegex(msg.text.c_str(), 1));
        telegramBot.sendMessage("Dry detection threshold set to: " + String(s_dryThershold) + " %");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif