
#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <SFML/Graphics.hpp>
#include "../headers/entity.hpp"

class MovableEntity : public Entity {

	public:
		void move();
		void move(sf::Vector2f g_speed);
		void setSpeed(sf::Vector2f g_speed);
		sf::Vector2f getSpeed();


	protected:
		sf::Vector2f speed;

	private:
};

#endif // MOVABLEENTITY_H
