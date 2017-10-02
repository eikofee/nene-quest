#include "../headers/world.hpp"

std::vector<Entity*> World::entities;
float World::elapsedTime;
void World::initialize() {
	
}

std::vector<Entity*> World::getEntities() {
	return entities;
}

std::vector<Entity*> World::getNearEntities(sf::Vector2f position, float radius) {
	std::vector<Entity*> result;
	for (auto e : entities)
		if (e->distanceToPosition(position) < radius)
			result.push_back(e);

	return result;
}

std::vector<Entity*> World::getCollidingEntities(Entity* entity) {
	std::vector<Entity*> result;
	for (auto e : entities)
		if (e != entity) {
			if (e->hasMultipleHitboxes()) {
				bool collide = false;
				for (auto h : e->getHitboxes())
					if (h->getGlobalBounds().intersects(entity->getHitbox().getGlobalBounds()) && !collide) {
						result.push_back(e);
						collide = true;
					}
			} else {
				if (e->getHitbox().getGlobalBounds().intersects(entity->getHitbox().getGlobalBounds()))
					result.push_back(e);
				//Add code for collision on z axis here
			}
		}

	return result;
}

std::vector<Entity*> World::testCollidingEntities(Entity* entity, sf::Vector2f movement) {
	std::vector<Entity*> result;
	sf::RectangleShape testHitbox = sf::RectangleShape(entity->getHitbox());
	testHitbox.move(movement);
	for (auto e : entities)
		if (e != entity) {
			if (e->hasMultipleHitboxes()) {
				bool collide = false;
				for (auto h : e->getHitboxes())
					if (h->getGlobalBounds().intersects(testHitbox.getGlobalBounds()) && !collide) {
						result.push_back(e);
						collide = true;
					}
			}
			else {
				if (e->getHitbox().getGlobalBounds().intersects(testHitbox.getGlobalBounds()))
					result.push_back(e);
				//Add code for collision on z axis here
			}
		}

	return result;
}

void World::setElapsedTime(float time) {
	elapsedTime = time / 1000;
}

void World::addEntity(Entity* entity) {
	entities.push_back(entity);
}

void World::updateEntities() {
	for (unsigned int i = 0; i < entities.size(); i++) {
		entities.at(i)->update(elapsedTime);
		if (entities.at(i)->isDead()) {
			delete(entities.at(i));
			entities.erase(entities.begin() + i);
		}
	}
}

float World::getElapsedTime() {
	return elapsedTime;
}