#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <SFML/Graphics.hpp>

#include "../headers/entity.hpp"

class MovableEntity : public Entity {

    public:
        MovableEntity();
        virtual ~MovableEntity();
        virtual void move(float elapsedTime);
		virtual void move(sf::Vector2f g_speed, float elapsedTime);
		void setSpeed(sf::Vector2f g_speed);
		sf::Vector2f getSpeed();
		bool isOnScreen(sf::Vector2u windowSize);

    protected:
        sf::Vector2f speed;

    private:
};

#endif // MOVABLEENTITY_H
