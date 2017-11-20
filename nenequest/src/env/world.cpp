#include <world.hpp>

std::vector<Entity*> World::entities;
std::vector<Player*> World::players;
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
			bool collide = false;
			for (auto h : e->getHitboxes())
				for (auto sh : entity->getHitboxes())
					if (h->getGlobalBounds().intersects(sh->getGlobalBounds()) && !collide) {
						result.push_back(e);
						collide = true;
					}
		}

	return result;
}

std::vector<Entity*> World::getCollidingEntitiesOnZAxis(Entity* entity) {
	std::vector<Entity*> result;
	for (auto e : entities)
		if (e != entity) {
			bool collide = false;
			for (auto h : e->getZHitboxes())
				for (auto sh : entity->getZHitboxes())
					if (h->getGlobalBounds().intersects(sh->getGlobalBounds()) && !collide) {
						result.push_back(e);
						collide = true;
					}
		}

	return result;
}

std::vector<Entity*> World::testCollidingEntities(Entity* entity, sf::Vector2f movement) {
	std::vector<Entity*> result;
	for (auto sh : entity->getHitboxes()) {
		sf::RectangleShape testHitbox = sf::RectangleShape(*sh);
		testHitbox.move(movement);
		for (auto e : entities)
			if (e != entity) {
				bool collide = false;
				for (auto h : e->getHitboxes())
					if (h->getGlobalBounds().intersects(testHitbox.getGlobalBounds()) && !collide) {
						result.push_back(e);
						collide = true;
					}
			}
	}

	return result;
}

std::vector<Entity*> World::testCollidingEntitiesOnZAxis(Entity* entity, sf::Vector2f movement) {
	std::vector<Entity*> result;
	for (auto sh : entity->getZHitboxes()) {

		sf::RectangleShape testHitbox = sf::RectangleShape(*sh);
		testHitbox.move(movement);
		for (auto e : entities)
			if (e != entity) {
				bool collide = false;
				for (auto h : e->getZHitboxes())
					if (h->getGlobalBounds().intersects(testHitbox.getGlobalBounds()) && !collide) {
						result.push_back(e);
						collide = true;
					}
			}
	}

	return result;
}

void World::setElapsedTime(float time) {
	elapsedTime = time / 1000;
}

void World::addEntity(Entity* entity, bool isPlayer) {
	entities.push_back(entity);
	if (isPlayer)
		players.push_back((Player*)entity);
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

void World::render(sf::RenderWindow &app) {
	for (auto e : entities)
		app.draw(*e);
}

std::vector<Player*> World::getPlayers() {
	return players;
}