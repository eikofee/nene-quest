#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <entity.hpp>
#include <player.hpp>
class World {
public:
	static void initialize();
	static std::vector<Entity*> getEntities();
	static std::vector<Entity*> getNearEntities(sf::Vector2f position, float radius);
	static std::vector<Entity*> getCollidingEntities(Entity* entity);
	static std::vector<Entity*> getCollidingEntitiesOnZAxis(Entity* entity);
	static void addEntity(Entity* entity, bool isPlayer = false);
	static void updateEntities();
	static void setElapsedTime(float time);
	static float getElapsedTime();
	static void render(sf::RenderWindow &app);
	static std::vector<Entity*> testCollidingEntities(Entity* entity, sf::Vector2f movement);
	static std::vector<Entity*> testCollidingEntitiesOnZAxis(Entity* entity, sf::Vector2f movement);
	static std::vector<Player*> getPlayers();

private:
	static std::vector<Entity*> World::entities;
	static std::vector<Player*> World::players;
	static float World::elapsedTime;
	static bool World::sortUsingFirstZHitbox(Entity* a, Entity* b);
};

#endif