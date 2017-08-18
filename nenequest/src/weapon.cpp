#include "../headers/weapon.hpp"

using namespace std;
using namespace sf;

Weapon::Weapon(WeaponType t)
{
    this->type = t;

    texture.loadFromFile(getWeaponPath(t));
	sprite.setTexture(texture);

    sprite.setOrigin(getWeaponOrigin(t));
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

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
