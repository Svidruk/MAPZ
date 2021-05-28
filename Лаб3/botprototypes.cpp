#include "botprototypes.h"


HTMLBot::HTMLBot(int BotID, QVector<QString> RS)
    : BotPrototype(BotID), RulesSet2(RS) {
}

BotPrototype *HTMLBot::Copy() const {
    return new HTMLBot(*this);
}

void HTMLBot::CallInterface() const{
    BotInterfaceFactory *BF = new BotInterfaceFactory();
    BotInterface *BI = new BotInterface(BF->CreateHTMLBotInterface());
    BI->workWithData(RulesSet2);
    delete BF;
    BI->show();
}

BotPrototype::BotPrototype(int BotId)
    : BotId(BotId) {}

BotPrototype::~BotPrototype(){
    //delete BI;
}

int BotPrototype::getId(){
    return BotId;
}

void BotPrototype::AllowRecording()
{
    recordingAllowed = true;
}

DOCBot::DOCBot(int BotID, QVector<QString> RS)
    : BotPrototype(BotID), RulesSet1(RS){
}

BotPrototype *DOCBot::Copy() const {
    return new DOCBot(*this);
}

void DOCBot::CallInterface() const{
    BotInterfaceFactory *BF = new BotInterfaceFactory();
    BotInterface *BI = new BotInterface(BF->CreateDOCBotInterface());
    BI->workWithData(RulesSet1);
    delete BF;
    BI->show();
}

PrototypeFactory::PrototypeFactory(int &id)
{
    RulesSetHtml.push_back("Parse as HTML");
    RulesSetDoc.push_back("Parse as DOC");
    bots[Type::HTMLBOT] =  new HTMLBot(id,RulesSetHtml);
    bots[Type::DOCBOT] = new DOCBot(id,RulesSetDoc);
    id++;
}

PrototypeFactory::~PrototypeFactory() {
    delete bots[Type::HTMLBOT];
    delete bots[Type::DOCBOT];
}

BotPrototype *PrototypeFactory::CreateBot(Type type) {
    return bots[type]->Copy();
}
