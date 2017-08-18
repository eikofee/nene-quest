#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "../headers/entity.hpp"
#include "../headers/weaponType.hpp"
#include <string>

class Weapon : public Entity {
    public :
        Weapon(WeaponType t);
        int getDamage();
        WeaponType getWeaponType();

        virtual void setPosition(float x, float y) {
            this->sprite.setPosition(sf::Vector2f(x,y));
            this->hitbox.setPosition(sf::Vector2f(x,y));
        }

        virtual void move(sf::Vector2f g_speed, float elapsedTime){
            hitbox.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
            sprite.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
        }

    private :
        WeaponType type;
        int damage;
};

#endif
