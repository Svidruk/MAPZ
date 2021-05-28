#include <iostream>
#include "Facade.h"
#include "Proxy.h"

void setRules(Bot *b) {
	b->pushRule("Parsing header");
	b->pushRule("Parsing body");
	b->pushRule("Parsing ending");
}

void setRules(abstractBot* b) {
	b->pushRule("Parsing header");
	b->pushRule("Parsing body");
	b->pushRule("Parsing ending");
}

int main()
{
	Bot* bot = new  Bot(1,"someBot");
	int i = 0;
	facade *f = new facade();
	std::cout << "press 1: to reset params of current unattended bot\npress other: to create attended bot 2: \n";
	std::cin >> i;
	switch (i)
	{
	case 1:
		setRules(bot);
		f->setExistingBot(bot);
		bot->runThread();
		f->setNewParams(bot);
		bot->runThread();
		break;
	default:
		abstractBot* ab = f->createAttended();
		setRules(ab);
		ab->runThread();
		//static_cast<AttendedBot*>(ab)->runThread();
		delete ab;
		break;
	}
	delete bot;
	delete f;
	return 0;
}
