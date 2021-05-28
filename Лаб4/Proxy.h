#pragma once
#include "abstractBot.h"
#include "Decorator.h"


class Bot : public abstractBot
{
public:
	Bot() {};
	Bot(int _id, std::string _name) {
		id = _id;
		name = _name;
		Busy = false;
	};
	~Bot() {};
	void pushRule(std::string _str) 
	{
		Rules.push_back(_str);
	}
	std::list<std::string> getRules() {
		return Rules;
	}
	void setRules(std::list <std::string> _rules) {
		Rules = _rules;
	}
	void workWithdData()
	{
		auto f2 = std::async(&Bot::runThread, this);
		f2.get();
	}
	void runThread() override
	{
		Busy = true;
		for (auto it = Rules.begin(); it != Rules.end(); it++) {
			std::cout <<  "\nCurrent operation: " + *it;
			for (int i = 0; i < 10; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				std::cout << ".";
			}
		}
		Busy = false;
	}
	bool isBusy() {
		return Busy;
	}
};

class BotProxy : public abstractBot
{
public:
	BotProxy(Bot* real_Bot) : _ProxyBot(new Bot(*real_Bot)) {
	}
	~BotProxy()
	{
		delete _ProxyBot;
	}
	void runThread() override{}
	void setBotProxy(std::list <std::string> _rules) 
    {
		_ProxyBot = new Bot();
		_ProxyBot->setRules(_rules);
	}
	void attemptOfParametersAcception(Bot* _b)
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			if (!_b->isBusy())
			{
				_b->setRules(_ProxyBot->getRules());
				std::cout << "\nNew parameters accepted !";
				return;
			}
		}
	}
	void AcceptNewParameters(Bot* _b)
	{
		auto f = std::async(&BotProxy::attemptOfParametersAcception,this, _b);
		//f.get();
	}
private:
    Bot* _ProxyBot;
	bool allowRecording = false;
};

