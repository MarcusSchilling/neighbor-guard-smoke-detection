#ifndef TELEGRAM_BOT_CPP
#define TELEGRAM_BOT_CPP

#include "../configuration/shared.credentials.h"
#include <FastBot.h>
#define FB_DYNAMIC // enable dynamic mode: the library takes longer to execute the request, but takes up 10 kb less memory in SRAM

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

    void deleteMessage(int32_t msgid)
    {
        fastBotTelegram.deleteMessage(msgid);
    }

    int32_t lastUsrMsg()
    {
        return fastBotTelegram.lastUsrMsg();
    }
};

#endif