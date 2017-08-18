#include "../headers/dragon.hpp"

using namespace sf;

Dragon::Dragon(Vector2f position){

	texture.loadFromFile("img/enemy_dragon.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, texture.getSize().y/2,texture.getSize().x/2, texture.getSize().y));
    sprite.setPosition(position);

	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

	speed = Vector2f(0.1,0);

}

Dragon::~Dragon(){
    //dtor
}

 void Dragon::update(float elapsedTime){

      if(clock.getElapsedTime().asSeconds() > 0.5){
        progressAnimation();
        clock.restart();
     }

    if(movement_timer++ > 50){
        speed = Vector2f( -speed.x, speed.y);
        movement_timer = 0;
    }

    this->move(elapsedTime);

    if(hp < 0);
        //destroy dragon

 }

 void Dragon::progressAnimation(){
    if(fire_breathing){

        if(animation_state == 0){
            animation_state = 1;
            sprite.setTextureRect(IntRect(texture.getSize().x/2, 0, texture.getSize().x, texture.getSize().y/2));
        }
        else{
            animation_state = 0;
            sprite.setTextureRect(IntRect(0, 0, texture.getSize().x/2, texture.getSize().y/2));
        }
    }
    else{
        if(animation_state == 0){
            animation_state = 1;
            sprite.setTextureRect(IntRect(texture.getSize().x/2 , texture.getSize().y/2, texture.getSize().x,texture.getSize().y));
        }
        else{
            animation_state = 0;
            sprite.setTextureRect(IntRect(0, texture.getSize().y/2,texture.getSize().x/2, texture.getSize().y));
        }

    }
}

void Dragon::breathFire(){
    fire_breathing = !fire_breathing;
}
