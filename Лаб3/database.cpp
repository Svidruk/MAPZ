#include "database.h"

std::mutex BotStorage::DBMutex;
BotStorage *BotStorage::PinstanceOfDataBase{nullptr};

BotStorage *BotStorage::GetInstance()
{
    DBMutex.lock();
    if(PinstanceOfDataBase == nullptr)
    {
        PinstanceOfDataBase =  new BotStorage();
    }
    return PinstanceOfDataBase;
}
