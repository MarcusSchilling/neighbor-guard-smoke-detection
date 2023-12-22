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
    NotificationStateHandler() : Handler("/notification-state", new NotificationRateHandler()){};

    void execute(FB_msg &msg)
    {
        s_notificationState = msg.text.substring(getRegexLength()).toInt();
        telegramBot.sendMessage("Notification state set to: " + msg.text.substring(getRegexLength()));
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif