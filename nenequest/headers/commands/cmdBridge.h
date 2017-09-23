#ifndef CMDBRIDGE_HPP_INCLUDED
#define CMDBRIDGE_HPP_INCLUDED

#include "../parserFunction.hpp"

class cmdBridge : public ParserFunction {


public:
	void initialize(LevelManager* manager) {
		this->commands.push_back("bridge");
		ParserFunction::manager = manager;
	}

	void exec(CustomMap* args) {
		int scrollSpeed = std::stoi(args->getOrDefault("speed", "1"));
		ParserFunction::manager->setScrollSpeed(scrollSpeed);
	}

};

#endif