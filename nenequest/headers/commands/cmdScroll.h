#ifndef CMDSCROLL_HPP_INCLUDED
#define CMDSCROLL_HPP_INCLUDED

#include "../parserFunction.hpp"

class cmdScroll : public ParserFunction {


public:
	void initialize(LevelManager* manager) {
		this->commands.push_back("scroll");
		ParserFunction::manager = manager;
	}

	void exec(std::map<std::string, std::string> args) {
		int scrollSpeed = std::stoi(args.at("speed"));
		ParserFunction::manager->setScrollSpeed(scrollSpeed);
	}

};

#endif