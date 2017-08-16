#include "../headers/boar.hpp"
#include <SFML/Graphics.hpp>

#include<stdio.h>
using namespace sf;

Boar::Boar(Vector2u windowSize, Vector2f position, Vector2f m_speed){

	texture.loadFromFile("img/obj_barrel.png");
	sprite.setTexture(texture);
    sprite.setPosition(position);

	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

	speed = m_speed;

	window_size = windowSize;

}

Boar::~Boar()
{
    //dtor
}
 void Boar::move() {

    if(!is_stunned){

        hitbox.move(speed);
        sprite.move(speed);
    }
    else{
        if(--stun_timer <= 0)
            is_stunned = false;
    }
}
void Boar::stun() {

    is_stunned = true;
    stun_timer = 100;
}
