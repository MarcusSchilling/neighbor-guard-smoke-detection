#ifndef UPDATE_RATE_HANDLER_CPP
#define UPDATE_RATE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./notification_state_handler.cpp"
class UpdateRateHandler : public Handler
{

public:
    UpdateRateHandler() : Handler("/update-rate", new NotificationStateHandler()){};

    void execute(FB_msg &msg)
    {
        s_updateRate = msg.text.substring(getRegexLength()).toDouble();
        telegramBot.sendMessage("Update rate set to: " + msg.text.substring(getRegexLength()) + " Hz");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif