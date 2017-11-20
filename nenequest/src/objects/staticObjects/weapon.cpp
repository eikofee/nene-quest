#include <weapon.hpp>

using namespace std;
using namespace sf;

Weapon::Weapon(WeaponType t)
{
    this->type = t;

    texture.loadFromFile(getWeaponPath(t));
	sprite.setTexture(texture);
	sf::RectangleShape* h = new sf::RectangleShape();
	h->setFillColor(sf::Color(255, 255, 0, 128));
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
