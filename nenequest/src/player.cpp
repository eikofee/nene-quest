#include "../headers/player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
/**
    TODO :
    - Placer l'arme correctement
    - Animation de l'attaque (rotation du sprite du Weapon)
    - Empêcher de sortir de la fenêtre / allez trop haut-bas
    - Detection avec les ennemis
    - Frame immortalité lorsqu'on perd de la vie
    - Saut (immortalité temporaire)
**/

using namespace sf;


Player::Player(Weapon* w, Vector2f position) { // 150,170

    this->weapon = w;
    this->life = LifeBar(PLAYER_HP);
    this->life.setPosition(300,100);
    // Player

	texture.loadFromFile("img/player1.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, texture.getSize().x/2, texture.getSize().y/3));
    sprite.setPosition(position);

    updateHitboxSize();
    updateHitboxPosition();

	// Weapon placement
    this->weapon->setPosition(position.x + 220, position.y + 180);

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
    this->is_attacking = true;
    update_animation();
    this->is_attacking = false;
}

void Player::equip(Weapon* w)
{
    this->weapon = w;
    this->weapon->setPosition(this->getPosition().x + 220, this->getPosition().y + 180);
}



void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    target.draw(*this->weapon, states);
    target.draw(this->life, states);
}

void Player::update_animation()
{
    this->animation_state = !this->animation_state;
    if (this->isJumping())
        return;

    float size_x = texture.getSize().x;
    float size_y = texture.getSize().y;

    int top_left_x, bottom_right_x, top_left_y, bottom_right_y;

    if (is_attacking) {
            top_left_x = size_x/2;
            bottom_right_x = size_x;
    } else {
            top_left_x = 0;
            bottom_right_x = size_x/2;
    }

    if (this->animation_state) { // jambes croisée
        top_left_y = size_y/3;
        bottom_right_y = size_y/3;
    } else {
        top_left_y = 0;
        bottom_right_y = size_y/3;
    }

    sprite.setTextureRect(IntRect(top_left_x, top_left_y, bottom_right_x, bottom_right_y));
}

void Player::move(Vector2f g_speed, float elapsedTime){

    if (clock.getElapsedTime().asSeconds() > this->ANIMATION_DELAY){
        update_animation();
        clock.restart();
    }

    hitbox.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
    sprite.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);

    this->getWeapon()->move(g_speed, elapsedTime);
}

LifeBar Player::getLife()
{
    return this->life;
}


bool Player::isJumping()
{
     return this->is_jumping;
}

void Player::switchJump()
{
    this->is_jumping = !this->is_jumping;
}
