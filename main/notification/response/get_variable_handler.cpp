#ifndef GET_VARIABLE_HANDLER_CPP
#define GET_VARIABLE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include "../../configuration/config.h"
#include "./labeling/smoke_label_handler.cpp"

class GetVariableHandler : public Handler
{

public:
    GetVariableHandler() : Handler("/get ([a-zA-Z]*)", new SmokeLabelHandler()) {} // RestartESPHandler()

    void execute(FB_msg &msg)
    {
        initConfigList();
        String variableName = parseRegex(msg.text, 1);
        if (!variableName.isEmpty() && configList.find(variableName) != configList.end())
        {
            std::variant<int, double, bool> value = configList[variableName];
            String message = "";
            if (std::holds_alternative<int>(value))
            {
                Serial.print("Step 4");
                int intValue = std::get<int>(value);
                message = variableName + ": " + String(intValue);
            }
            else if (std::holds_alternative<bool>(value))
            {
                bool boolValue = std::get<bool>(value);
                message = variableName + ": " + (boolValue ? "true" : "false");
            }
            else if (std::holds_alternative<double>(value))
            {
                double doubleValue = std::get<double>(value);
                message = variableName + ": " + String(doubleValue, 2); // Display with 2 decimal places
            }
            Serial.print("Step 5");
            telegramBot.sendMessage(message);
        }
        else
        {
            String configVariables = "";
            for (const auto &pair : configList)
            {
                configVariables = configVariables + pair.first + "\n";
            }
            String messageReply = "Variable not defined. Currently defined variables:\n" + configVariables;
            telegramBot.sendMessage(messageReply);
        }
        Serial.print("Step 6");
        telegramBot.deleteMessage(msg.messageID);
    }
};

#endif
