#include "../headers/background.hpp"

using namespace sf;

Background::Background(Vector2u v) {
	//Cloud stuff
	this->v = v;
	srand(time(NULL));

    int x = v.x;
    int y = v.y;

    this->sky = RectangleShape(Vector2f(x, y/3));
    this->sky.setFillColor(Color(115, 195, 226));

    this->ground = RectangleShape(Vector2f(x, y - this->sky.getSize().y));
    this->ground.setFillColor(Color(189, 132, 100));
    this->ground.setPosition(0, this->sky.getSize().y);
}

void Background::update() {
	std::vector<RandomCloud>::iterator i = this->clouds.begin();
	while (i != this->clouds.end()) {
		bool active = (*i).isAlive();
		if (active)
		{
			(*i).translate(-3, 0);
			++i;
		}
		else
			this->clouds.erase(i++);
	}

	this->createClouds();
}

void Background::createClouds() {
	float t = this->clock.getElapsedTime().asSeconds();
	if (t >= this->nextCloud) {
		RandomCloud* nc = new RandomCloud();
		nc->setPosition(v.x + 250 /*cloud width*/, rand() % this->CLOUD_SPAWN_Y_BOTTOM + this->CLOUD_SPAWN_Y_TOP);
		nc->generateBorder();
		this->clouds.insert(clouds.begin(), *nc);

		this->nextCloud = rand() % (this->CLOUD_SPAWN_INTERVAL_RANDOM * 2) - this->CLOUD_SPAWN_INTERVAL_RANDOM + this->CLOUD_SPAWN_INTERVAL;
		this->clock.restart();
	}
}