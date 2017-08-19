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

 	sprite.move(speed.x * elapsedTime, speed.y*elapsedTime);
 	updateHitboxPosition();
}

void MovableEntity::move(Vector2f g_speed, float elapsedTime){

 	sprite.move(g_speed.x * elapsedTime, g_speed.y*elapsedTime);
    updateHitboxPosition();
}
