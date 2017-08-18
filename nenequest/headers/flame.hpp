#ifndef FLAME_H
#define FLAME_H

#include <SFML/Graphics.hpp>
#include "../headers/movableEntity.hpp"

class Flame : public MovableEntity {

    public :
        Flame();
        Flame(sf::Vector2f position, float f);
        virtual ~Flame();
        virtual void update(float elapsedTime);
        bool isDead();

    private :
        float span_left = 0;
        float lifeSpan = 0;
        float fact;
        sf::Vector2f loc;
        bool is_dead = false;
};

#endif // FLAME_H
