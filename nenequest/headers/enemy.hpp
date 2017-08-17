#ifndef ENNEMY_H
#define ENNEMY_H

#include "../headers/entity.hpp"
#include <SFML/Graphics.hpp>

class Enemy : public Entity
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
