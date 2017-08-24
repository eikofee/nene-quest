#ifndef PARSERFUNCTION_HPP_INCLUDED
#define PARSERFUNCTION_HPP_INCLUDED

#include <string>
#include <vector>
#include <map>

class ParserFunction {

private:
	std::vector<std::string> commands;
	

public:
	ParserFunction();
	bool isCorrect(std::string command);
	virtual void exec(std::map<std::string, std::string> args) const = 0;
	
};

#endif