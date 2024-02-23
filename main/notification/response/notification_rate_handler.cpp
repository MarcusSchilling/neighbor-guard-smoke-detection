#ifndef NOTIFICATION_RATE_HANDLER_CPP
#define NOTIFICATION_RATE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include <string>
#include "./restart_esp_handler.cpp"

class NotificationRateHandler : public Handler
{

public:
    NotificationRateHandler() : Handler("/notificationRate ([1-9]*\\.[0-9]*|[0-9]*)", new RestartESPHandler()){};

    void execute(FB_msg &msg)
    {
        s_notificationRate = parseRegex(msg.text, 1).toDouble();
        telegramBot.sendMessage("Notification rate set to: " + String(s_notificationRate, 2) + " minutes");
    }
};

#endif