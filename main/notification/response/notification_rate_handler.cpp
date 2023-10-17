#ifndef NOTIFICATION_RATE_HANDLER_CPP
#define NOTIFICATION_RATE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
// #include "./_handler.cpp"
class NotificationRateHandler : public Handler
{
public:
    NotificationRateHandler() : Handler("/notification-rate", nullptr){};

    void execute(FB_msg &msg)
    {
        s_notificationRate = msg.text.substring(18).toInt();
        telegramBot.sendMessage("Notification rate set to: " + msg.text.substring(18) + " minutes");
        // fastBot.attach(newMsg);
    }
    // void newMsg(FB_msg &msg)
    // {
    //     SmokeThresholdHandler startHandler;
    //     startHandler.handleRequest(msg);
    // }
};

#endif