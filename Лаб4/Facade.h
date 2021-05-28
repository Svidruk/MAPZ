#pragma once
#include <iostream>
#include <string>
#include "Proxy.h"
#include "Decorator.h"

class RuleSetter
{
public:
	std::list<std::string> RuleCreator() {
		std::list<std::string> rules;
		int i = 0;
		std::cout << "Select parsing order\n";
		std::cout << "press 1: to parse header; \npress 2: to parse and replace header by new data;\npress other: skip;\n";
		std::cin >> i;
		switch (i)
		{
		case 1:
			rules.push_back("parsing header");
			break;
		case 2:
			rules.push_back("parsing and replacing header");
			break;
		default:
			break;
		}
		i = 0;
		std::cout << "press 1: to parse body; \npress 2: to parse and replace body by new data;\npress other: skip;\n";
		std::cin >> i;
		switch (i)
		{
		case 1:
			rules.push_back("parsing body");
			break;
		case 2:
			rules.push_back("parsing and replacing body");
			break;
		default:
			break;
		}
		i = 0;
		std::cout << "press 1: to parse ending; \npress 2: to parse and replace ending by new data;\npress other: skip;\n";
		std::cin >> i;
		switch (i)
		{
		case 1:
			rules.push_back("parsing ending\n");
			break;
		case 2:
			rules.push_back("parsing and replacing ending\n");
			break;
		default:
			break;
		}
		return rules;
	}
};

class botFactory
{
public:
	BotProxy* createProxyBot(Bot* b, std::list<std::string> rules)
	{
		int i = 0;
		BotProxy* _b = new BotProxy(b);
		_b->setBotProxy(rules);
		return _b;
	}
	abstractBot* createAttendedBot(abstractBot* ab) {
		return new AttendedBot(ab);
		 
	}
};


class facade 
{
public:
	void setExistingBot(Bot* b)
	{
		int i = 0;
		RuleSetter* rs = new RuleSetter();
		botFactory* bf = new botFactory();
		std::list<std::string> rules = rs->RuleCreator();
		bp = bf->createProxyBot(b, rules);
		delete rs;
		delete bf;
	}
	abstractBot* createAttended()
	{
		botFactory* bf = new botFactory();
		abstractBot* ab = new Bot(2, "someOtherBot");
		abstractBot* decoratedBot = new AttendedBot(ab);
		delete bf;
		delete ab;
		return decoratedBot;
	};
	void setNewParams(Bot* b) 
	{
		bp->AcceptNewParameters(b);
	}
	BotProxy* bp;
	abstractBot* ab;
};

