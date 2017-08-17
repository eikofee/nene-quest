#ifndef ENNEMY_H
#define ENNEMY_H

#include "../headers/movableEntity.hpp"
#include <SFML/Graphics.hpp>

class Enemy : public MovableEntity
{
    public:
        Enemy();
        virtual ~Enemy();

    protected:
        short int hp;
        sf::Clock clock;
        int animation_state = 0;

    private:
};

#endif // ENNEMY_H
