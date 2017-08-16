#include "../headers/movableEntity.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

void MovableEntity::setSpeed(sf::Vector2f g_speed){

	speed = g_speed;
}

Vector2f MovableEntity::getSpeed(){

    return speed;
}

 void MovableEntity::move(){

 	hitbox.move(speed);
 	sprite.move(speed);
 }

  void MovableEntity::move(Vector2f g_speed){

 	hitbox.move(g_speed);
 	sprite.move(g_speed);
 }
