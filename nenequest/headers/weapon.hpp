#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "../headers/entity.hpp"
#include "../headers/weaponType.hpp"
#include <string>

class Weapon : Entity {
    public :
        Weapon(WeaponType t, sf::Vector2f position);
        int getDamage();
        WeaponType getWeaponType();

    private :
        WeaponType type;
        int damage;
};

#endif
