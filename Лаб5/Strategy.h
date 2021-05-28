#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <list>


class ParsingInstruction
{
public:
    virtual ~ParsingInstruction() {}
    virtual std::vector<std::vector<std::string>> Parse(std::string data) const = 0;
};

class ParseArticle : public ParsingInstruction
{
public:
    std::vector<std::vector<std::string>> Parse(std::string data) const override
    {
        std::vector<std::vector<std::string>> result;
        int i = 0;
        int start = 0;
        int end = data.find("\n");
        while (end != -1) 
        {
            result[i].push_back(data.substr(start, end - start));
            if (result[i].back().find("header")) {
                result[i].back().append("HEADER");
            }
            else if(result[i].back().find("body"))
            {
                result[i].back().append("BODY");
            }
            start = end + 1;
            end = data.find("\n", start);
            i++;
        }
        i++;
        result[i].push_back(data.substr(start, end - start));
        return result;
    }
};
class ParseOutlay : public ParsingInstruction
{
    std::vector<std::vector<std::string>> Parse(std::string data) const override
    {
        std::vector<std::vector<std::string>> result;
        int i = 0;
        int start = 0;
        int end = data.find("\n");
        while (end != -1)
        {
            result[i].push_back(data.substr(start, end - start));
            if (i == 0)
            {
                result[i].back().append("Year income: ");
                int monthlyIncome = std::stoi(result[i].back());
                i++;
                result[i].push_back(std::to_string(monthlyIncome/12));
                result[i].back().append("Monthly income: ");
            }
            else if (i == 2)
            {
                result[i].push_back(data.substr(start, end - start));
                result[i].back().append("other expenses: ");
            }
            start = end + 1;
            end = data.find("\n", start);
            i++;
        }
        if (i == 2)
        {
            result[i].push_back(data.substr(start, end - start));
            result[i].back().append("other expenses: ");
        }
        return result;
    }
};

class Bot
{
public:
    Bot(ParsingInstruction* parsing_instructions_ = nullptr) : parsingInstructions(parsing_instructions_){}
    ~Bot()
    {
        delete this->parsingInstructions;
    }
    void setInstructions(ParsingInstruction* parsing_instructions_)
    {
        delete this->parsingInstructions;
        this->parsingInstructions = parsing_instructions_;
    }
    void pushData(std::string data) {
        currentData = data;
    }
    void ParseDataAccordingToInstructions() const
    {
        std::cout << "Parse data according to new instructions\n";
        std::vector<std::vector<std::string>> result = this->parsingInstructions->Parse(currentData);
        for (size_t i = 0; i < result.size(); i++)
        {
            std::cout << result[i].data() << "\n";
        }
    }
private:
    ParsingInstruction* parsingInstructions;
    std::string currentData;
};

void TestStrategy()
{
    std::string s = "Some header\nSome body\n";
    Bot* bot = new Bot(new ParseArticle);
    std::cout << "Bot: parse data in one way.\n";
    bot->pushData(s);
    bot->ParseDataAccordingToInstructions();
    std::cout << "\n";
    std::string s2 = "130420\n12300\n";
    std::cout << "Bot: parse data in other way.\n";
    bot->pushData(s2);
    bot->setInstructions(new ParseOutlay);
    bot->ParseDataAccordingToInstructions();
    delete bot;
}
