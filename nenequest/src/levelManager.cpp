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
	game->addPlayer(new Player(Sword, sf::Vector2f(1000,600)));
}

void LevelManager::spawnChest(int x, int y, BonusType bonus, int hp) {
	game->addObject(new BreakableObject(Chest, sf::Vector2f(x,y)), bonus);
}

// Game setters
void LevelManager::setBackground(Background* bck) {
	this->background = bck;
}

void LevelManager::setGame(Game* gme){
    this->game = gme;
}

bool LevelManager::pccomp(ParserCommand* a, ParserCommand* b) {
	if (a->getTime() >= b->getTime())
		return false;

	return true;
}

