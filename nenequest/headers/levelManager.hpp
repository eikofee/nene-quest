#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "../headers/parserCommand.hpp"
#include "background.hpp"
class Game;
class LevelManager {

private:
	std::string name;
	std::list<ParserCommand*> levelCommands;
	sf::Clock clock;
	Background* background;
	Game* game;
	float timeSync;
	bool isWaiting;

public:
	LevelManager();
	void setBackground(Background* bck);
	void setLevelCommands(std::vector<ParserCommand*> commands);
	void update();
	void wait();
	void resume();

	// Function mapping
	void setScrollSpeed(int speed);
	void startLevel(int playerCount);
	void spawnChest(int x, int y, std::string item, int hp);

	static bool pccomp(ParserCommand* a, ParserCommand* b);
};

#endif