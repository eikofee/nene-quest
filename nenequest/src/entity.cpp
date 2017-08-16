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

