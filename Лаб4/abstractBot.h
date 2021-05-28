#pragma once
#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

class abstractBot
{
public:
	abstractBot() {};
	virtual ~abstractBot() {};
	//virtual void workWithdData() const = 0;
	virtual void runThread() = 0;
	void pushRule(std::string str) {
		Rules.push_back(str);
	}
protected:
	int id;
	std::string name;
	std::list <std::string> Rules;
	std::list <std::string> processedData;
	bool Busy;
};