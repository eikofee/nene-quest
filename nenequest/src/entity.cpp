#include "../headers/entity.hpp"
#include <math.h>
using namespace sf;

bool Entity::detectHit(Entity* entity){

    if(this->getDepth() + DEPTH_DIFF > entity->getDepth() && this->getDepth() - DEPTH_DIFF < entity->getDepth())
        return entity->getHitbox().getGlobalBounds().intersects(hitbox.getGlobalBounds());
    return false;
}

RectangleShape Entity::getHitbox() {
	return hitbox;
}

RectangleShape Entity::getZHitbox() {
	return zHitbox;
}

std::vector<sf::RectangleShape*> Entity::getHitboxes() {
	return hitboxes;
}

std::vector<sf::RectangleShape*> Entity::getZHitboxes() {
	return zHitboxes;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    //target.draw(hitbox, states);
	target.draw(sprite, states);
}

void Entity::setPosition(int x, int y)
{
	sprite.setPosition(x,y);
	hitbox.setPosition(x,y);
}

Vector2f Entity::getPosition() {
    return hitbox.getPosition();
}

void Entity::updateHitboxPosition(){
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
}

void Entity::updateHitboxSize(){
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
}

Vector2f Entity::getSpriteSize(){
    return Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Entity::updateSpritePosition(){
	sprite.setPosition(hitbox.getGlobalBounds().left, hitbox.getGlobalBounds().top);
}

float Entity::getDepth(){
    return hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height;
}

float Entity::getDrawDepth(){
    return this->getDepth();
}

void Entity::move(sf::Vector2f v) {
	//maybe we can do it directly here instead of each of the entities
	sprite.move(v);
	hitbox.move(v);
}

EntityType Entity::getEntityType() {
	return NONE;
}

void Entity::update(float elapsedTime) {
	//do nothing
}

bool Entity::isDead() {
	return false;
}

float Entity::distanceToPosition(sf::Vector2f position) {
	return sqrtf(powf(this->getPosition().x - position.x, 2) + powf(this->getPosition().y - position.y, 2));
}

bool Entity::hasMultipleHitboxes() {
	return hitboxes.size() > 0;
}

bool Entity::hasMultipleZHitboxes() {
	return zHitboxes.size() > 0;
}