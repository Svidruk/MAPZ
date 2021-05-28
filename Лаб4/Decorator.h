#pragma once
#include "abstractBot.h"
#include <fstream>

class DecoratorBot : public abstractBot
{
public:
	DecoratorBot(abstractBot* bot) : bot(bot) {
	}
	void runThread() override
	{
		return this->bot->runThread();
	}
protected:
	abstractBot *bot;
};


class AttendedBot : public DecoratorBot//, protected Bot
{
public:
	AttendedBot(abstractBot* bot) : DecoratorBot(bot){}
	/*void pushRule(std::string str)  {
		Rules.push_back(str);
	}*/
	void runThread() override
	{
		Busy = true;
		for (auto it = Rules.begin(); it != Rules.end(); it++) {
			std::cout << "\nCurrent operation: " + *it;
			for (int i = 0; i < 10; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				std::cout << ".";
			}
			std::string sentence = *it;
			sentence = sentence.substr(sentence.find_first_of(" \t") + 1);
			processedData.push_back(sentence);
		}
		std::ofstream recordedData;
		recordedData.open("myFile.txt");
		recordedData.clear();
		for (auto it = processedData.begin(); it != processedData.end(); it++) {
			recordedData <<"some processed " + *it << "\n";
		}
		std::cout << "\nProcessed data\n";
		for (auto it = processedData.begin(); it != processedData.end(); it++) {
			std::cout << *it << "\n";
		}
		Busy = false;
		system("pause");
		return;
	}
};


