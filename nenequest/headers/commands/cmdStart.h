#ifndef CMDSTART_HPP_INCLUDED
#define CMDSTART_HPP_INCLUDED

#include "../parserFunction.hpp"

class cmdStart : public ParserFunction {


public:
	void initialize(LevelManager* manager) {
		this->commands.push_back("start");
		ParserFunction::manager = manager;
	}

	void exec(CustomMap* args) {
		ParserFunction::manager->startLevel();
	}

};

#endif