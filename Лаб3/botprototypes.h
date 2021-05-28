#ifndef BOTPROTOTYPES_H
#define BOTPROTOTYPES_H


#include <QString>
#include <QHash>
#include "botinterface.h"


class Rules{
public:
    int getI() const
    {
        return i;
    }

    void setI(int value)
    {
        i = value;
    }

private:
    int i;
};

enum Type {
    HTMLBOT = 0,
    DOCBOT
};


class BotPrototype {
protected:
    int BotId;
    QVector<QString> RulesSet;
    bool recordingAllowed = false;

 public:
    BotPrototype() {}
    BotPrototype(int BotId);
    virtual ~BotPrototype();
    virtual void CallInterface() const =0;
    virtual BotPrototype* Copy() const = 0;
    int getId();
    virtual void AllowRecording();
};

class DOCBot : public BotPrototype {
    private:
    QVector<QString> RulesSet1;

    public:
    DOCBot(int BotID, QVector<QString> RS);
    BotPrototype *Copy() const override;
    void CallInterface()const override;
};

class HTMLBot : public BotPrototype {
private:
    QVector<QString> RulesSet2;
public:
    HTMLBot(int BotID,  QVector<QString> RS);
    BotPrototype *Copy() const override;
    void CallInterface()const override;
};

class PrototypeFactory {
private:
    QVector<QString> RulesSetHtml;
    QVector<QString> RulesSetDoc;
    QHash<Type, BotPrototype* > bots;

public:
    PrototypeFactory(int &id);

    ~PrototypeFactory();

    BotPrototype *CreateBot(Type type);
};

#endif
