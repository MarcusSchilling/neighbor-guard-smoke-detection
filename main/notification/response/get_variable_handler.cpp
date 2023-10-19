#ifndef GET_VARIABLE_HANDLER_CPP
#define GET_VARIABLE_HANDLER_CPP

#include "handler.hpp"
#include "../telegram_bot.cpp"
#include <cstdio>
#include "../../configuration/config.h"
#include "./restart_esp_handler.cpp"
class GetVariableHandler : public Handler
{

public:
    GetVariableHandler() : Handler("/get", new RestartESPHandler()) {}

    void execute(FB_msg &msg)
    {
        initConfigList();
        String variableName = msg.text.substring(getRegexLength());
        Serial.println("Variable handling message: " + msg.text);
        Serial.println("Variable name: " + variableName);

        if (!variableName.isEmpty() && configList.find(variableName.c_str()) != configList.end())
        {
            std::variant<int,double,bool> value = configList[variableName.c_str()];
            if (std::holds_alternative<int>(value))
            {
                int intValue = std::get<int>(value);
                String message = variableName + ": " + String(intValue);
                telegramBot.sendMessage(message);
            }
            else if (std::holds_alternative<bool>(value))
            {
                bool boolValue = std::get<bool>(value);
                String message = variableName + ": " + (boolValue ? "true" : "false");
                telegramBot.sendMessage(message);
            }
            else if (std::holds_alternative<double>(value))
            {
                double doubleValue = std::get<double>(value);
                String message = variableName + ": " + String(doubleValue, 2); // Display with 2 decimal places
                telegramBot.sendMessage(message);
            }
        }
        else
        {
            String configVariables = "";
            for (const auto& pair : configList)
            {
                configVariables = configVariables + pair.first.c_str() + "\n";
            }
            String messageReply = "Variable not defined. Currently defined variables:\n" + configVariables;
            telegramBot.sendMessage(messageReply);
        }
    }
};

#endif
