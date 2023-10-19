#ifndef RESTART_ESP_HANDLER_CPP
#define RESTART_ESP_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"

class RestartESPHandler : public Handler
{

public:
    RestartESPHandler() : Handler("/restart", nullptr) {}

    void execute(FB_msg &msg)
    {
        ESP.restart();
    }
};

#endif
