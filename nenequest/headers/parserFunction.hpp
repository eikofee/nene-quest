#ifndef PARSERFUNCTION_HPP_INCLUDED
#define PARSERFUNCTION_HPP_INCLUDED

#include <string>
#include <vector>
#include <levelManager.hpp>
#include <customMap.hpp>

class ParserFunction {

protected:
	std::vector<std::string> commands;
	LevelManager* manager;

public:
	ParserFunction();
	virtual void initialize(LevelManager* manager);
	bool isCorrect(std::string command);
	virtual void exec(CustomMap* args);
	
};

#endif
