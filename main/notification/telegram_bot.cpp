#ifndef TELEGRAM_BOT
#define TELEGRAM_BOT

#include "../configuration/credentials.h"
#include <FastBot.h>
class TelegramBot
{
private:
    FastBot fastBotTelegram{BOT_TOKEN};

public:
    TelegramBot()
    {
        fastBotTelegram.setChatID(CHAT_ID);
    }

    void initialize()
    {
    }

    void sendMessage(String message)
    {
        fastBotTelegram.sendMessage(message);
    }
};

#endif