#include "../headers/entity.hpp"
using namespace sf;

bool Entity::detectHit(Entity entity){

	return entity.getHitbox().getGlobalBounds().intersects(hitbox.getGlobalBounds());
}

RectangleShape Entity::getHitbox(){

	return hitbox;
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
    return sprite.getPosition();
}

void Entity::updateHitboxPosition(){
    //hitbox.setFillColor(Color::Red);
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
}

void Entity::updateHitboxSize(){
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
}
