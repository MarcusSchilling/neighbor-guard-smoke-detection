#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "../telegram_bot.cpp"
class Handler
{
private:
    String regex;
    Handler *next;

protected:
    TelegramBot telegramBot;

    Handler(String regex, Handler *next) : regex(regex), next(next)
    {
    }

public:

    void handleRequest(FB_msg &msg)
    {
        if (isResponsible(msg)) {
            execute(msg);
        } else if(next){
            next->handleRequest(msg);
        } else {
            telegramBot.sendMessage("Invalid Input");
        }
    }

    bool isResponsible(FB_msg &msg)
    {
        // return msg.text.indexOf(regex) != -1;
        return msg.text.startsWith(regex);
    }
    String getRegex()
    {
        return regex;
    }
    int getRegexLength()
    {
        return regex.length()+1;
    }

    virtual void execute(FB_msg &msg) = 0;
};

#endif