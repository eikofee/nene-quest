#include <background.hpp>
using namespace sf;

Background::Background(Vector2u v) {
	//Cloud stuff
	this->v = v;
	srand(time(NULL));

    int x = v.x;
    int y = v.y;

    this->sky = RectangleShape(Vector2f(x, y/2.5f));
    this->sky.setFillColor(Color(115, 195, 226));

    this->ground = RectangleShape(Vector2f(x, y - this->sky.getSize().y));
    this->ground.setFillColor(Color(189, 132, 100));
    this->ground.setPosition(0, this->sky.getSize().y);
}

void Background::update() {
	for (int i = 0; i < this->clouds.size(); i++) {
		bool active = this->clouds.at(i)->isAlive();
		if (active) {
			this->clouds.at(i)->translate(- (scrollSpeed + 1) * cloudSpeedModifier, 0);
			this->clouds.at(i)->update();
		}
		else {
			delete(this->clouds.at(i));
			this->clouds.erase(this->clouds.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < this->mountains.size(); i++) {
		bool active = this->mountains.at(i)->isAlive();
		if (active) {
			this->mountains.at(i)->translate(- scrollSpeed * mountainSpeedModifier, 0);
			this->mountains.at(i)->update();
		}
		else {
			delete(this->mountains.at(i));
			this->mountains.erase(this->mountains.begin() + i);
			i--;
		}
	}

	this->createClouds();
	this->createMountains();
}

void Background::createClouds() {
	float t = this->cloudClock.getElapsedTime().asSeconds();
	if (t * scrollSpeed >= this->nextCloud) {
		RandomCloud* nc = new RandomCloud();
		nc->setPosition(v.x + 250 /*cloud width*/, rand() % this->CLOUD_SPAWN_Y_BOTTOM + this->CLOUD_SPAWN_Y_TOP);
		nc->generateBorder();
		this->clouds.insert(clouds.begin(), nc);

		this->nextCloud = rand() % (this->CLOUD_SPAWN_INTERVAL_RANDOM * 2) - this->CLOUD_SPAWN_INTERVAL_RANDOM + this->CLOUD_SPAWN_INTERVAL;
		this->cloudClock.restart();
	}
}

void Background::createMountains() {
	float t = this->mountainClock.getElapsedTime().asSeconds();
	if (t * scrollSpeed >= this->nextMountain) {
		RandomMountain* nm = new RandomMountain();
		nm->setPosition(v.x + 250 /*cloud width*/, this->sky.getSize().y + MOUNTAIN_VAR_Y_OFFSET);
		this->mountains.insert(mountains.begin(), nm);

		this->nextMountain = rand() % (this->MOUNTAIN_SPAWN_INTERVAL_RANDOM * 2) - this->MOUNTAIN_SPAWN_INTERVAL_RANDOM + this->MOUNTAIN_SPAWN_INTERVAL;
		this->mountainClock.restart();
	}
}

void Background::setSpeed(int speed) {
	this->scrollSpeed = speed;
}

float Background::getSkyHeight(){
    return this->sky.getLocalBounds().height;
}
