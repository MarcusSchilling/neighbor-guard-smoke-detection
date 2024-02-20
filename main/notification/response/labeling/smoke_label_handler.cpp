#ifndef SMOKE_LABEL_HANDLER_CPP
#define SMOKE_LABEL_HANDLER_CPP

#include "../handler.hpp"
#include "../../../configuration/config.h"
#include "../restart_esp_handler.cpp"
class SmokeLabelHandler : public Handler
{
public:
    SmokeLabelHandler() : Handler("/smoke", new RestartESPHandler()){};

    void execute(FB_msg &msg)
    {
        s_smokeLabel = true;
        telegramBot.sendMessage("Thank you for labeling smoke");
    }
};
#endif