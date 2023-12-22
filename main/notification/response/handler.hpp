#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "../telegram_bot.cpp"
#include <regex>

class Handler
{
private:
    std::string regex;
    Handler *next;


protected:
    TelegramBot telegramBot;

    Handler(std::string regex, Handler *next) : regex(regex), next(next)
    {
    }

    std::string parseRegex(const std::string &input, const int requestedGroup)
    {
        std::regex regexObj(regex);
        std::smatch match;

        if (std::regex_search(input, match, regexObj))
        {
            // The first group is index 1 in the match object
            return match[requestedGroup].str();
        }
        else
        {
            // Return an empty string if no match is found
            return "";
        }
    }

public:
    void handleRequest(FB_msg &msg)
    {
        if (isResponsible(msg))
        {
            execute(msg);
        }
        else if (next)
        {
            next->handleRequest(msg);
        }
        else
        {
            telegramBot.sendMessage("Invalid Input");
            int32_t usrMsg = telegramBot.lastUsrMsg();
            telegramBot.deleteMessage(usrMsg);
            telegramBot.deleteMessage(msg.messageID);
            Serial.println("Message deleted with ID: " + String(usrMsg));
        }
    }

    bool isResponsible(FB_msg &msg)
    {
        return std::regex_match(msg.text.c_str(), std::regex(regex.c_str()));
    }

    int getRegexLength()
    {
        return regex.length() + 1;
    }

    virtual void execute(FB_msg &msg) = 0;
};

#endif