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
	h->setOrigin(getWeaponOrigin(t));
    updateAutoHitboxSize();
    updateAutoHitboxPosition();
	h->setPosition(h->getPosition() + getWeaponOffset(t));
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

void Weapon::Animate(float lerp) {
	if (lerp <= 0.5f)
		lerp *= 2;
	else
		lerp = (0.5f - (lerp - 0.5f)) * 2;
	sprite.setRotation(lerp * 60);
	hitboxes.at(0)->setRotation(sprite.getRotation());
}

void Weapon::setPosition(float x, float y)
{
	sprite.setPosition(sf::Vector2f(x, y) + getWeaponOffset(type));
	hitboxes.at(0)->setPosition(sprite.getPosition());
}
