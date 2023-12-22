#ifndef HOT_THRESHOLD_HANDLER_CPP
#define HOT_THRESHOLD_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./cool_threshold_handler.cpp"
class HotThresholdHandler : public Handler
{

public:
    HotThresholdHandler() : Handler("/hotThreshold ((|[+-])[0-9]*)", new CoolThresholdHandler()){};

    void execute(FB_msg &msg)
    {
        s_hotTempThershold = std::stoi(parseRegex(msg.text.c_str(), 1));
        Serial.println("Hot handling message: " + msg.text);
        telegramBot.sendMessage("Heat warning detection threshold set to: " + String(s_hotTempThershold) + " °C");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif