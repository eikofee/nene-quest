#include <iostream>
#include <randomMountain.hpp>

using namespace std;
using namespace sf;

RandomMountain::RandomMountain() {
	float edge = rand() % (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT;
	float angle = rand() % (2 * RANDOM_ANGLE) - RANDOM_ANGLE;
	this->body = new RectangleShape(Vector2f(edge, edge));
	this->body->setFillColor(Color(0xB7, 0xCA, 0x74));
	this->body->setOrigin(this->body->getSize().x / 2, this->body->getSize().y / 2);
	this->body->setRotation(45 + angle);
}

RandomMountain::~RandomMountain() {
	delete this->body;
}

void RandomMountain::update() {
	if (this->body->getPosition().x < (0 - this->MAX_HEIGHT))
		this->alive = false;
}

bool RandomMountain::isAlive() {
	return this->alive;
}

void RandomMountain::translate(float x, float y) {
	this->body->move(x, y);
}
