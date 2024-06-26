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
    NotificationStateHandler() : Handler("/notificationState ([0-3]|1[1-3])\b", new NotificationRateHandler()){};

    void execute(FB_msg &msg)
    {
        s_notificationState = parseRegex(msg.text, 1).toInt();
        telegramBot.sendMessage("Notification state set to: " + String(s_notificationState));
    }
};

#endif