#include "../headers/levelManager.hpp"

LevelManager::LevelManager() {
	this->timeSync = 0;
	this->isWaiting = false;
}

void LevelManager::setLevelCommands(std::vector<ParserCommand*> commands) {
	for (auto c : commands)
		this->levelCommands.push_back(c);

	this->levelCommands.sort(pccomp);
}

void LevelManager::update() {
	if (!isWaiting && this->levelCommands.size() > 0)
		if (this->levelCommands.front()->getTime() <= (this->timeSync + this->clock.getElapsedTime().asSeconds())) {
			ParserCommand* c = this->levelCommands.front();
			this->levelCommands.pop_front();
			c->getFunction()->exec(new CustomMap(&(c->getArguments())));
			this->update();
		}
}

void LevelManager::wait() {
	timeSync += clock.getElapsedTime().asSeconds();
	isWaiting = true;
}

void LevelManager::resume() {
	clock.restart();
	isWaiting = false;
}

// Function mapping
void LevelManager::setScrollSpeed(int speed) {
	this->background->setSpeed(speed);
}

void LevelManager::startLevel() {
	//init player and stuff
}

void LevelManager::spawnChest(int x, int y, std::string item, int hp) {
	//spawn a chest on the given position
}



// Game setters
void LevelManager::setBackground(Background* bck) {
	this->background = bck;
}


bool LevelManager::pccomp(ParserCommand* a, ParserCommand* b) {
	if (a->getTime() >= b->getTime())
		return false;
	
	return true;
}

