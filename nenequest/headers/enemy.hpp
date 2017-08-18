#ifndef ENNEMY_H
#define ENNEMY_H

#include "../headers/movableEntity.hpp"
#include <SFML/Graphics.hpp>

class Enemy : public MovableEntity
{
    public:
        Enemy();
        virtual ~Enemy();
        short int getAttackDamage();

    protected:
        short int hp;
        sf::Clock clock;
        short int animation_state = 0;
        short int attack_damage;



    private:
};

#endif // ENNEMY_H
