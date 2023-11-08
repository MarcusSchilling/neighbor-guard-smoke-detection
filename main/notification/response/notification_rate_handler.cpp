#ifndef NOTIFICATION_RATE_HANDLER_CPP
#define NOTIFICATION_RATE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./get_variable_handler.cpp"
class NotificationRateHandler : public Handler
{

public:
    NotificationRateHandler() : Handler("/notification-rate", nullptr){}; // new GetVariableHandler()){};

    void execute(FB_msg &msg)
    {
        s_notificationRate = msg.text.substring(getRegexLength()).toDouble();
        telegramBot.sendMessage("Notification rate set to: " + msg.text.substring(getRegexLength()) + " minutes");
    }
};

#endif