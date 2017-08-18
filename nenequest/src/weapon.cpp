#include "../headers/weapon.hpp"

using namespace std;
using namespace sf;

Weapon::Weapon(WeaponType t, Vector2f position)//string path, Vector2f position, int damage)
{
    this->type = t;

    texture.loadFromFile(getWeaponPath(t));
	sprite.setTexture(texture);
    sprite.setPosition(position);

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
