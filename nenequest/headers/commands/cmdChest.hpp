#ifndef CMDCHEST_HPP_INCLUDED
#define CMDCHEST_HPP_INCLUDED

#include "parserFunction.hpp"
#include <random>

class cmdChest : public ParserFunction {


public:
	void initialize(LevelManager* manager) {
		this->commands.push_back("chest");
		ParserFunction::manager = manager;
	}

	void exec(CustomMap* args) {
		auto hp = std::stoi(args->getOrDefault("hp", "1"));
		auto item = args->getOrDefault("item", "none");
		auto x = std::stoi(args->getOrDefault("x", "-1"));
		auto y = std::stoi(args->getOrDefault("y", "-1"));
		auto randx_max = std::stoi(args->getOrDefault("randx_max", "1.5"));
		auto randx_min = std::stoi(args->getOrDefault("randx_min", "1"));
		auto randy_max = std::stoi(args->getOrDefault("randy_max", "0.9"));
		auto randy_min = std::stoi(args->getOrDefault("randy_min", "0.4"));
		if (x == -1)
			x = rand() * (randx_max - randx_min) + randx_min;

		if (y == -1)
			y = rand() * (randy_max - randy_min) + randy_min;
		
		ParserFunction::manager->spawnChest(x, y, item, hp);
	}

};

#endif