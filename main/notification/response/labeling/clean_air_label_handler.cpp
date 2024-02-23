#ifndef CLEAN_AIR_LABEL_HANDLER_CPP
#define CLEAN_AIR_LABEL_HANDLER_CPP

#include "../handler.hpp"
#include "../../../configuration/config.h"
#include "../restart_esp_handler.cpp"
class CleanAirLabelHandler : public Handler
{
public:
    CleanAirLabelHandler() : Handler("/clean", nullptr){};

    void execute(FB_msg &msg)
    {
        s_cleanAirLabel = true;
        telegramBot.sendMessage("Thank you for labeling clean air");
    }
};
#endif