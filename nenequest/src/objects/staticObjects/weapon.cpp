#include "weapon.hpp"

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

	int spriteWidth = sprite.getLocalBounds().width;
	int spriteHeight = sprite.getLocalBounds().height;

    sprite.setOrigin(getWeaponOrigin(t));
	if (t == WeaponType::Bow) {
		this->sprite.setTextureRect(IntRect(0, 0, this->texture.getSize().x, this->texture.getSize().y / 2));
		spriteHeight /= 2;
	}

	h->setOrigin(getWeaponOrigin(t));
    updateAutoHitboxSize();
    updateAutoHitboxPosition();
	h->setPosition(h->getPosition() + getWeaponOffset(t));
    this->damage = damage;
	auto zh = new sf::RectangleShape();
	zh->setFillColor(sf::Color(0, 0, 255, 128));
	zh->setSize(Vector2f(spriteWidth, spriteHeight / 5));
	zh->setPosition(h->getPosition() + h->getSize() - zh->getSize());
	zHitboxes.push_back(zh);
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
	sprite.setPosition(hitboxes.at(0)->getPosition() + lerp * sf::Vector2f(-5, 10));
}

void Weapon::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y) + getWeaponOffset(type));
	hitboxes.at(0)->setPosition(sprite.getPosition());
	zHitboxes.at(0)->setPosition(sprite.getPosition() - sf::Vector2f(0, zHitboxes.at(0)->getSize().y));
}
