#include "../headers/dragon.hpp"

using namespace sf;

Dragon::Dragon(Vector2f position){

	texture.loadFromFile("img/enemy_dragon.png");
	sprite.setTexture(texture);
    sprite.setPosition(position);

	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

	speed = Vector2f(0.1,0);

}

Dragon::~Dragon(){
    //dtor
}

 void Dragon::update(float elapsedTime){

    if(movement_timer++ > 50){
        speed = Vector2f( -speed.x, speed.y);
        movement_timer = 0;
    }

    this->move(elapsedTime);

    if(hp < 0);
        //destroy dragon

 }
