#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <entity.hpp>
class World {
public:
	static void initialize();
	static std::vector<Entity*> getEntities();
	static std::vector<Entity*> getNearEntities(sf::Vector2f position, float radius);
	static std::vector<Entity*> getCollidingEntities(Entity* entity);
	static std::vector<Entity*> getCollidingEntitiesOnZAxis(Entity* entity);
	static void addEntity(Entity* entity);
	static void updateEntities();
	static void setElapsedTime(float time);
	static float getElapsedTime();
	static std::vector<Entity*> testCollidingEntities(Entity* entity, sf::Vector2f movement);
	static std::vector<Entity*> testCollidingEntitiesOnZAxis(Entity* entity, sf::Vector2f movement);

private:
	static std::vector<Entity*> World::entities;
	static float World::elapsedTime;
};

#endif