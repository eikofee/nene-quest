#include "../headers/player.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Player::Player(Weapon* w, Vector2f position) : LivingEntity(PLAYER_HP) {

    this->weapon = w;

    // Player
	texture.loadFromFile("img/icon_p2.png");
	sprite.setTexture(texture);
    sprite.setPosition(position);
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

	// Weapon placement
    this->weapon->setPosition(this->getPosition().x,this->getPosition().y);
}

Player::~Player(){
    delete this->weapon;
}


Weapon* Player::getWeapon()
{
    return this->weapon;
}

void Player::attack()
{
    /** TODO **/
}

void Player::equip(Weapon* w)
{
    this->weapon = w;
}



void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    target.draw(*this->weapon, states);
}


void Player::move(Vector2f g_speed, float elapsedTime){

    hitbox.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
    sprite.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);

    this->getWeapon()->move(g_speed, elapsedTime);
}
