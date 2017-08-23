#define _USE_MATH_DEFINES


#include "../headers/arrow.hpp"
#include<math.h>

using namespace sf;

Arrow::Arrow(Vector2f position)
{
    initial_location = position;
    lifespan = 0;

	texture.loadFromFile("img/weapon_arrow.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(position);
    //sprite.scale(0.5,0.5);

    updateHitboxSize();
    hitbox.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    updateHitboxPosition();

	speed = Vector2f(0.8,-0.8);
}

Arrow::~Arrow()
{
    //dtor
}

void Arrow::update(float elapsedTime){

    float g = 0.002;

    lifespan += elapsedTime;

    //Make the arrow follow a curve
    this->setPosition(initial_location.x + lifespan*speed.x,initial_location.y + lifespan*speed.y + g*lifespan*lifespan/2);
    sprite.setRotation(atan((speed.y + g*lifespan)/speed.x)*180/3.1415);
    hitbox.setRotation(sprite.getRotation());

    if(this->getPosition().y > initial_location.y + 300)
        is_dead = true;
}

bool Arrow::isDead(){
    return is_dead;
}

void Arrow::kill(){
    is_dead = true;
}
