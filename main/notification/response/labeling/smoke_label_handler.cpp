#ifndef SMOKE_LABEL_HANDLER_CPP
#define SMOKE_LABEL_HANDLER_CPP

#include "../handler.hpp"
#include "../../../configuration/config.h"

class SmokeLabelHandler : public Handler
{
public:
    SmokeLabelHandler() : Handler("/smoke", nullptr){};

    void execute(FB_msg &msg)
    {
        s_smokeLabel = true;
    }
};
#endif