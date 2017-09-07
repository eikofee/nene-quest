#ifndef PARSERFUNCTION_HPP_INCLUDED
#define PARSERFUNCTION_HPP_INCLUDED

#include <string>
#include <vector>
#include <map>
class LevelManager;
class ParserFunction {

protected:
	std::vector<std::string> commands;
	LevelManager* manager;

public:
	ParserFunction();
	virtual void initialize(LevelManager* manager);
	bool isCorrect(std::string command);
	virtual void exec(std::map<std::string, std::string> args);
	
};

#endif