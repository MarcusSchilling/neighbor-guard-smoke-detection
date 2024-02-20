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
    UpdateRateHandler() : Handler("/updateRate ([1-9]*\\.[0-9]*|[0-9]*)", new NotificationStateHandler()){};

    void execute(FB_msg &msg)
    {
        s_updateRate = parseRegex(msg.text, 1).toDouble();
        telegramBot.sendMessage("Update rate set to: " + String(s_updateRate, 2) + " Hz");
    }
};

#endif