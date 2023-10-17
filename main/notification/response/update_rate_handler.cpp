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
    UpdateRateHandler() : Handler("/update-rate", nullptr){};

    void execute(FB_msg &msg)
    {
        s_updateRate = msg.text.substring(12).toInt();
        telegramBot.sendMessage("Update rate set to: " + msg.text.substring(12) + " Hz");
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        NotificationStateHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif