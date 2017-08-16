#include "../headers/entity.hpp"

using namespace sf;

bool Entity::detectHit(Entity entity){

	return entity.getHitbox().getGlobalBounds().intersects(hitbox.getGlobalBounds());
}

RectangleShape Entity::getHitbox(){

	return hitbox;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	target.draw(sprite, states);
}

void Entity::setPosition(int x, int y)
{
	sprite.setPosition(x,y);
	hitbox.setPosition(x,y);
}

void Entity::setSpeed(sf::Vector2f g_speed){

	speed = g_speed;
}

Vector2f Entity::getSpeed(){

    return speed;
}

 void Entity::move(){

 	hitbox.move(speed);
 	sprite.move(speed);
 }

  void Entity::move(Vector2f g_speed){

 	hitbox.move(g_speed);
 	sprite.move(g_speed);
 }
