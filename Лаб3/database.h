#ifndef DATABASE_H
#define DATABASE_H

#include <QVector>
#include <chrono>
#include <thread>
#include <mutex>
#include "botprototypes.h"
#include <QtCore/QObject>

class BotStorage
{

private:
    static BotStorage *PinstanceOfDataBase;
    static std::mutex DBMutex;

protected:
    BotStorage(){}

    ~BotStorage(){}

    QVector<BotPrototype*> BotBase;

public:
    BotStorage(BotStorage &other) = delete;

    void operator=(const BotStorage &) = delete;

    static BotStorage *GetInstance();

    void setBot(BotPrototype* d)
    {
        BotBase.push_back(d);
        DBMutex.unlock();
    }

    BotPrototype* getBotByIdx(int idx)
    {
        for (int i = 0; i < BotBase.size(); i++)
        {
            if(idx == BotBase[i]->getId())
            {
                DBMutex.unlock();
                return BotBase[i];
            }
        }
    }

    int getSize(){
        if(PinstanceOfDataBase == nullptr){
            return 0;
        }
        return BotBase.size();
    }
};

#endif // DATABASE_H
