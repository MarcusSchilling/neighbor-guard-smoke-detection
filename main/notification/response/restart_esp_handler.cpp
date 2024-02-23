#ifndef RESTART_ESP_HANDLER_CPP
#define RESTART_ESP_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include "../../configuration/config.h"
#include "get_variable_handler.cpp"
class RestartESPHandler : public Handler
{

public:
    RestartESPHandler() : Handler("/restart", new GetVariableHandler()) {}

    void execute(FB_msg &msg)
    {
        ESP.restart();
    }
};

#endif
