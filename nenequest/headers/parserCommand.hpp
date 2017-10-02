#ifndef PARSERCOMMAND_H
#define PARSERCOMMAND_H

#include <string>
#include <map>
#include "../headers/parserFunction.hpp"

class ParserCommand {

private:
	float time;
	std::string name;
	std::map<std::string, std::string> arguments;
	ParserFunction* function;

public:
	ParserCommand();
	void setTime(float time);
	void setName(std::string name);
	void setFunction(ParserFunction* function);
	void addArgument(std::string key, std::string value);
	float getTime();
	std::string getName();
	ParserFunction* getFunction();
	std::map<std::string, std::string>* getArguments();

};

#endif
