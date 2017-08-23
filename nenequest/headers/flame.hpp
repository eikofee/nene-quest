#ifndef FLAME_H
#define FLAME_H

#include <SFML/Graphics.hpp>
#include "../headers/movableEntity.hpp"

class Flame : public MovableEntity {

    public :
        static int const FLAMES_DAMAGE = 1;
        Flame();
        Flame(sf::Vector2f position, float f);
        virtual ~Flame();
        void update(float elapsedTime);
        bool isDead();

    private :
        float span_left = 0;
        float lifespan = 0;
        float fact;
        sf::Vector2f initial_location;
        bool is_dead = false;
};

#endif // FLAME_H
