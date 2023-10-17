#ifndef NOTIFICATION_STATE_HANDLER_CPP
#define NOTIFICATION_STATE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./notification_rate_handler.cpp"
class NotificationStateHandler : public Handler
{
public:
    NotificationStateHandler() : Handler("/notification-state", nullptr){};

    void execute(FB_msg &msg)
    {
        s_notificationState = msg.text.substring(19).toInt();
        telegramBot.sendMessage("Notification state set to: " + msg.text.substring(19));
        fastBot.attach(newMsg);
    }
    void newMsg(FB_msg &msg)
    {
        NotificationRateHandler startHandler;
        startHandler.handleRequest(msg);
    }
};

#endif