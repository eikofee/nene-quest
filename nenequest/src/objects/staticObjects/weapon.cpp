#include <weapon.hpp>

using namespace std;
using namespace sf;

Weapon::Weapon(WeaponType t)
{
    this->type = t;

    texture.loadFromFile(getWeaponPath(t));
	sprite.setTexture(texture);
	sf::RectangleShape* h = new sf::RectangleShape();
	hitboxes.push_back(h);

    sprite.setOrigin(getWeaponOrigin(t));
    updateAutoHitboxSize();
    updateAutoHitboxPosition();

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
