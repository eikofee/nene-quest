#include "../headers/config.hpp"
#include "../headers/player.hpp"
#include "../headers/world.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
/**
    TODO (not updated) :
    - Placer l'arme correctement
    - Animation de l'attaque (rotation du sprite du Weapon)
    - Empecher de sortir de la fenere / allez trop haut-bas => Fait dans game.cpp <= and fixed back here
    - Detection avec les ennemis => Fait dans game.cpp 
    - Frame immortalite lorsqu'on perd de la vie => Fait dans game.cpp mais c'est mieux ici donc fait le +(animation clignotante dans l'ideal)
    - Saut (immortalite temporaire) => Fait dans game.cpp <= need to be here
**/

using namespace sf;
using namespace std;

Player::Player(Weapon* w, Vector2f position, bool secondPlayer) { // 150,170

    this->weapon = w;
    if (!secondPlayer) {
        this->life = new LifeBar(PLAYER_HP, Vector2f(300,100), PlayerID::PLAYER1);
        this->texture.loadFromFile(PACKAGE_DATADIR "/img/player1.png");
    } else {
        this->life = new LifeBar(PLAYER_HP, Vector2f(800,100), PlayerID::PLAYER2);
		this->texture.loadFromFile(PACKAGE_DATADIR "/img/player2.png");
    }

	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(IntRect(0, 0, this->texture.getSize().x/2, this->texture.getSize().y/3));
	this->hitbox.setPosition(position);
	this->hitbox.setSize(Vector2f(this->sprite.getLocalBounds().width, this->sprite.getLocalBounds().height));
    updateSpritePosition();

	// Weapon placement
    this->weapon->setPosition(position.x + 220, position.y + 180);
}

Player::~Player(){
    delete this->weapon;
}

Weapon* Player::getWeapon(){
    return this->weapon;
}

void Player::attack(){
    this->is_attacking = true;
    update_animation();
    this->is_attacking = false;
}

void Player::equip(Weapon* w){
    this->weapon = w;
    this->weapon->setPosition(this->getPosition().x + 220, this->getPosition().y + 180);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //target.draw(hitbox,states);
    target.draw(this->sprite, states);
    target.draw(*this->weapon, states);
    target.draw(*this->life, states);
}

void Player::update_animation(){
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

void Player::move(Vector2f g_speed){
	float elapsedTime = World::getElapsedTime();

    if (clock.getElapsedTime().asSeconds() > this->ANIMATION_DELAY) {
        update_animation();
        clock.restart();
    }

    hitbox.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
    sprite.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
	this->getWeapon()->move(g_speed, elapsedTime);
	//TOFIX
	if (World::getCollidingEntities(this).size() > 0) {
		hitbox.move(-g_speed.x * elapsedTime, -g_speed.y*elapsedTime);
		sprite.move(-g_speed.x * elapsedTime, -g_speed.y*elapsedTime);
		this->getWeapon()->move(-g_speed, elapsedTime);
	}
}

LifeBar* Player::getLife(){
    return this->life;
}

bool Player::isJumping(){
     return this->is_jumping;
}

void Player::toggleJump(){
    this->is_jumping = !this->is_jumping;
}

void Player::setPosition(float x, float y){
    this->sprite.setPosition(x, y);
    this->hitbox.setPosition(x, y);
    this->weapon->setPosition(this->getPosition().x + 220, this->getPosition().y + 180);
}

void Player::fireArrow(){
    arrows.push_back(new Arrow(Vector2f(this->getPosition().x + 220, this->getPosition().y + 180), this->getDepth()));
}

void Player::update(float elapsedTime){
	this->cleanArrows(elapsedTime);
	this->manageMovements();
}

void Player::manageMovements() {
	Vector2f finalMovement = Vector2f(0, 0);
	if (this->moving_up)
		finalMovement.y -= PLAYER_SPEED;
	if (this->moving_down)
		finalMovement.y += PLAYER_SPEED;
	if (this->moving_left)
		finalMovement.x -= PLAYER_SPEED;
	if (this->moving_right)
		finalMovement.x += PLAYER_SPEED;

	finalMovement = this->fixMovements(finalMovement);
	this->move(finalMovement);
	this->fixPosition();
}

sf::Vector2f Player::fixMovements(sf::Vector2f movement) {
	Vector2f result = Vector2f(movement.x, movement.y);
	if (this->hitbox.getGlobalBounds().left + result.x < 0)
		result.x = 0;
		//result.x = -this->hitbox.getGlobalBounds().left;

	if (this->hitbox.getGlobalBounds().left + this->hitbox.getGlobalBounds().width + result.x > 1920 /*Gameroom size (right)*/)
		result.x = 0;
		//result.x = 1920 - this->hitbox.getGlobalBounds().left - this->hitbox.getGlobalBounds().width;

	//TODO
	if (this->hitbox.getGlobalBounds().top + result.y < 200 /*Gameroom size (top)*/)
		result.y = 0;
		//result.y = 500 - this->hitbox.getGlobalBounds().top;

	if (this->hitbox.getGlobalBounds().top + this->hitbox.getGlobalBounds().height + result.y > 1080 /*Gameroom size (bottom)*/)
		result.y = 0;
		//result.y = 1080 - this->hitbox.getGlobalBounds().top - this->hitbox.getGlobalBounds().height;
	
	
	return result;
}

void Player::fixPosition() {
	sf::FloatRect bounds = this->hitbox.getGlobalBounds();
	sf::Vector2f v = Vector2f(0, 0);
	if (bounds.left < 0)
		v.x = -bounds.left;

	if (bounds.left + bounds.width > 1920)
		v.x = (1920 - bounds.left - bounds.width);

	if (bounds.top < 200)
		v.y = -1 * (bounds.top - 200);

	if (bounds.top + bounds.height > 1080)
		v.y = (1080 - bounds.top - bounds.height);

	this->move(v);

}

void Player::cleanArrows(float elapsedTime) {
	for (unsigned int i = 0; i< this->arrows.size(); i++) {
		this->arrows.at(i)->update(elapsedTime);
		if (this->arrows.at(i)->isDead()) {
			delete(this->arrows.at(i));
			this->arrows.erase(this->arrows.begin() + i);
		}
	}
}

void Player::setLastDroppedItem(ItemWeapon* item){
    last_dropped_item = item;
}

ItemWeapon* Player::getLastDroppedItem(){
    return last_dropped_item;
}

vector<Arrow*> Player::getArrows(){
    return arrows;
}
