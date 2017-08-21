#include "../headers/movableEntity.hpp"

using namespace sf;

MovableEntity::MovableEntity()
{
    //ctor
}

MovableEntity::~MovableEntity()
{
    //dtor
}

void MovableEntity::setSpeed(sf::Vector2f g_speed){

	speed = g_speed;
}

Vector2f MovableEntity::getSpeed(){

    return speed;
}

void MovableEntity::move(float elapsedTime){

 	hitbox.move(speed.x * elapsedTime, speed.y*elapsedTime);
 	updateSpritePosition();
}

void MovableEntity::move(Vector2f g_speed, float elapsedTime){

 	hitbox.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
    updateSpritePosition();
}

bool MovableEntity::isOnScreen(Vector2u windowSize){
    if(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width < 0 || hitbox.getGlobalBounds().left > windowSize.x)
        return false;
    if(hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height > windowSize.y || hitbox.getGlobalBounds().top < 0)
        return false;
    return true;
}
