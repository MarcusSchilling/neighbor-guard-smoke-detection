#ifndef SMOKE_LABEL_HANDLER_CPP
#define SMOKE_LABEL_HANDLER_CPP

#include "../handler.hpp"
#include "../../../configuration/config.h"
#include "./clean_air_label_handler.cpp"

class SmokeLabelHandler : public Handler
{
public:
    SmokeLabelHandler() : Handler("/smoke", new CleanAirLabelHandler()){};

    void execute(FB_msg &msg)
    {
        s_smokeLabel = true;
        telegramBot.sendMessage("Thank you for labeling smoke");
    }
};
#endif