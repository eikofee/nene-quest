#include "../headers/weapon.hpp"

using namespace std;
using namespace sf;

Weapon::Weapon(WeaponType t)
{
    this->type = t;

    texture.loadFromFile(getWeaponPath(t));
	sprite.setTexture(texture);

    sprite.setOrigin(getWeaponOrigin(t));
    updateHitboxSize();
    updateHitboxPosition();

    this->damage = damage;
}

int Weapon::getDamage()
{
    return this->damage;
}

WeaponType Weapon::getWeaponType()
{
    return this->type;
}
