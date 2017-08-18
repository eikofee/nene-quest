#ifndef ENNEMY_H
#define ENNEMY_H

#include "../headers/movableEntity.hpp"
#include "../headers/livingEntity.hpp"
#include <SFML/Graphics.hpp>

class Enemy : public MovableEntity, public LivingEntity
{
    public:
        Enemy(int hp);
        virtual ~Enemy();
        short int getAttackDamage();
        void update(float elapsedTime);

    protected:
        sf::Clock clock;
        short int animation_state = 0;
        short int attack_damage;



    private:
};

#endif // ENNEMY_H
