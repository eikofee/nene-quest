#include "../headers/boar.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Boar::Boar(Vector2u windowSize, Vector2f position, Vector2f g_speed){

	texture.loadFromFile("img/enemy_boar_anim.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,256,256));
    sprite.setPosition(position);

	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	hitbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

	speed = g_speed;

}

Boar::~Boar(){
    //dtor
}

void Boar::progressAnimation(){
    if(animation_state == 0){
        animation_state = 1;
        sprite.setTextureRect(IntRect(0,256,256,512));
    }
    else{
        animation_state = 0;
        sprite.setTextureRect(IntRect(0,0,256,256));
    }
}

 void Boar::update(float elapsedTime) {

     if(clock.getElapsedTime().asSeconds() > 0.1){
        progressAnimation();
        clock.restart();
     }

    //Move the boar if he isn't stunned
    if(!is_stunned){
        this->move(elapsedTime);
    }
    else{
        if(--stun_timer <= 0)
            is_stunned = false;
    }

    //Check if the boar is still in the screen
    if(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width < 0 || hitbox.getGlobalBounds().left > window_size.x);
        //destroy boar

    if(hp < 0);
        //Destroy boar
}
void Boar::stun() {

    is_stunned = true;
    stun_timer = 100;
}
