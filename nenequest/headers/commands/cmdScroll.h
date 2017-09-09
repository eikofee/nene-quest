#ifndef CMDSCROLL_HPP_INCLUDED
#define CMDSCROLL_HPP_INCLUDED

#include "../parserFunction.hpp"

class cmdScroll : public ParserFunction {


public:
	void initialize(LevelManager* manager) {
		this->commands.push_back("scroll");
		ParserFunction::manager = manager;
	}

	void exec(CustomMap* args) {
		int scrollSpeed = std::stoi(args->getOrDefault("speed", "1"));
		ParserFunction::manager->setScrollSpeed(scrollSpeed);
	}

};

#endif
