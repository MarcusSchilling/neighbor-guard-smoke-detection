#ifndef GET_MEASUREMENT_HANDLER_CPP
#define GET_MEASUREMENT_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include "../../configuration/config.h"
#include "../../observer/data_logger.hpp"
#include "./labeling/smoke_label_handler.cpp"

extern Measurement lastMeasurement;
class GetMeasurementHandler : public Handler
{

public:
    GetMeasurementHandler() : Handler("/measure", new SmokeLabelHandler()) {}

    void execute(FB_msg &msg)
    {
        telegramBot.sendMessage(
            lastMeasurement.toString({MeasurementAttributes::rZero,
                                      MeasurementAttributes::correctedRZero,
                                      MeasurementAttributes::ppm,
                                      MeasurementAttributes::cppm,
                                      MeasurementAttributes::resistance,
                                      MeasurementAttributes::temperature,
                                      MeasurementAttributes::humidity}));
    }
};

#endif
