#pragma once
#include <iostream>
#include <list>
#include <string>
#include <chrono>
#include <thread>

class IBotStateObserver {
public:
    virtual ~IBotStateObserver() {};
    virtual void Update(const std::string& message_from_subject) = 0;
};

class IBot {
public:
    virtual ~IBot () {};
    virtual void Attach(IBotStateObserver* observer) = 0;
    virtual void Detach(IBotStateObserver* observer) = 0;
    virtual void Notify() = 0;
};

class attendedBot : public IBot {
public:
    virtual ~attendedBot() {
        std::cout << "transition to sleep mode\n";
    }
    void Attach(IBotStateObserver* client) override {
        clients.push_back(client);
    }
    void Detach(IBotStateObserver* client) override {
        clients.remove(client);
    }
    void Notify() override {
        std::list<IBotStateObserver*>::iterator iterator = clients.begin();
        while (iterator != clients.end()) {
            (*iterator)->Update(message);
            ++iterator;
        }
    }
    void CreateMessage(std::string msg = "Empty") {
        this->message = msg;
        Notify();
    }
    void DoWork(std::string data) 
    {
        Busy = true;
        message = "BOT: Wait for a while i'm imitating some job";
        Notify();
        std::this_thread::sleep_for(std::chrono::seconds(5));
        message = "BOT: Some imaginary job is done";
        Notify();
        Busy = false;
    }

private:
    std::list<IBotStateObserver*> clients;
    std::string message;
    bool Busy;
};

class Client : public IBotStateObserver {
public:
    Client(attendedBot& b) : bot(b) 
    {
        this->bot.Attach(this);
        std::cout << "Hello i'm Client "<< Client::clientsCount <<": and i'm watching you\n";
        this->number_ = Client::clientsCount++;
    }
    virtual ~Client()
    {
        std::cout << "Client " << this->number_ << ": is logged out.\n";
    }
    void Update(const std::string& message_from_subject) override {
        messageFromBot = message_from_subject;
        PrintInfo();
    }
    void PrintInfo() {
        std::cout << "message for Client " << this->number_ << ":\n " << this->messageFromBot << "\n";
    }

private:
    std::string messageFromBot;
    attendedBot& bot;
    static int clientsCount;
    int number_;
};

int Client::clientsCount = 0;

void TestObserver() {
    attendedBot* bot = new attendedBot();
    Client* client = new Client(*bot);
    Client* client2 = new Client(*bot);
    bot->DoWork("parse this string");
    
    delete client;
    delete bot;
}