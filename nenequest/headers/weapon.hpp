#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <entity.hpp>
#include <weaponType.hpp>
#include <string>

class Weapon : public Entity {
    public :
        Weapon(WeaponType t);
        int getDamage();
        WeaponType getWeaponType();

    private :
        WeaponType type;
        int damage;
};

#endif
