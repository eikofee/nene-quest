#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include "entity.hpp"
#include "weaponType.hpp"
using namespace sf;

class Weapon : public Entity {
   public:
    Weapon(WeaponType t);
    int getDamage();
    WeaponType getWeaponType();
    void Animate(float lerp);
    void setPosition(int x, int y);

   private:
    int weaponDamageByType(WeaponType t);
    WeaponType type;
    int damage;
};

#endif
