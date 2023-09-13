#ifndef TELEGRAM_BOT
#define TELEGRAM_BOT

#include "../configuration/credentials.h"
#include <FastBot.h>
class TelegramBot
{
private:
    FastBot fastBot{BOT_TOKEN};

public:
    TelegramBot()
    {
        fastBot.setChatID(CHAT_ID);
    }

    void initialize()
    {
    }

    void sendMessage(String message)
    {
        fastBot.sendMessage(message);
    }
};
#endif