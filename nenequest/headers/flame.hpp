#ifndef FLAME_H
#define FLAME_H

#include <SFML/Graphics.hpp>
#include "../headers/projectile.hpp"

class Flame : public Projectile {

    public :
        static int const FLAMES_DAMAGE = 1;
        Flame();
        Flame(sf::Vector2f position, float f, float g_depth);
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
