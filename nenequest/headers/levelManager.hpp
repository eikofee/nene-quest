#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <string>
#include <vector>
#include <list>
#include "..\headers\parserCommand.hpp"
#include <SFML\Graphics.hpp>
class LevelManager {

private:
	std::string name;
	std::list<ParserCommand*> levelCommands;
	sf::Clock clock;
	float timeSync;
	bool isWaiting;

public:
	LevelManager();
	void setLevelCommands(std::vector<ParserCommand*> commands);
	void update();
	void wait();
	void resume();

	static bool pccomp(ParserCommand* a, ParserCommand* b);
};

#endif