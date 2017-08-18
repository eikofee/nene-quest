#include "../headers/flame.hpp"
#include<stdio.h>
using namespace sf;

Flame::Flame()
{
    //ctor
}

Flame::Flame(Vector2f position, float f){
    initial_location = position;
    fact = f;

	texture.loadFromFile("img/icon_fire.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(position);
    sprite.scale(0.5,0.5);

	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

	speed = Vector2f(-2.7,1);

}

void Flame::update(float elapsedTime){
    float x = (this->getPosition().x - initial_location.x) / 25;

    lifespan += elapsedTime;

    this->setPosition(this->getPosition().x + elapsedTime*speed.x/10,initial_location.y + 2*fact *sin(lifespan/(9*fact)));

    if(cos(lifespan/(9*fact)) > 0 && sprite.getScale().x <= 1)
        sprite.setScale(sprite.getScale().x + 0.01, sprite.getScale().y + 0.01);
    else{
        span_left += elapsedTime;
        sprite.setScale(sprite.getScale().x - 0.01, sprite.getScale().y - 0.01);
    }
    if(span_left > 800)
        is_dead = true;

}

bool Flame::isDead(){

return is_dead;
}
Flame::~Flame()
{
    //dtor
}
