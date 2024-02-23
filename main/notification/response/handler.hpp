#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "../telegram_bot.cpp"
#include <regex>
#include <optional>

class Handler
{
private:
    const std::string regex;
    Handler *next;

protected:
    Handler(const std::string regex, Handler *next) : regex(regex), next(next)
    {
    }

    String parseRegex(const String &input, const int requestedGroup)
    {
        std::regex regexObj(regex);
        std::smatch match;
        std::string inputConverted = std::string(input.c_str());
        if (std::regex_search(inputConverted, match, regexObj))
        {
            return String(match.str(requestedGroup).c_str());
        }
        else
        {
            // Return an empty string if no match is found
            return "";
        }
    }

    virtual ~Handler()
    {
        delete next;
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
        }
    }

    bool isResponsible(FB_msg &msg)
    {
        return std::regex_match(msg.text.c_str(), std::regex(regex));
    }

    int getRegexLength()
    {
        return regex.length() + 1;
    }

    virtual void execute(FB_msg &msg) = 0;
};

#endif