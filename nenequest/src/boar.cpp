#include "../headers/boar.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Boar::Boar(Vector2u windowSize, Vector2f position, Vector2f g_speed) : Enemy (3) {

    attack_damage = 1;

	texture.loadFromFile("img/enemy_boar_anim.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,texture.getSize().x,texture.getSize().y/2));
    sprite.setPosition(position);

    updateHitboxSize();
    updateHitboxPosition();

	speed = g_speed;

}

Boar::~Boar(){
    //dtor
}

void Boar::progressAnimation(){
    if(animation_state == 0){
        animation_state = 1;
        sprite.setTextureRect(IntRect(0,texture.getSize().y/2,texture.getSize().x,texture.getSize().y));
    }
    else{
        animation_state = 0;
        sprite.setTextureRect(IntRect(0,0,texture.getSize().x,texture.getSize().y/2));
    }
}

 void Boar::update(float elapsedTime) {


    //Move the boar if he isn't stunned
    if(!is_stunned){
        this->move(elapsedTime);
        if(clock.getElapsedTime().asSeconds() > 0.1){
            progressAnimation();
            clock.restart();
     }

    }
    else{
        if(--stun_timer <= 0)
            is_stunned = false;
    }

    //Check if the boar is still in the screen
    if(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width < 0 || hitbox.getGlobalBounds().left > window_size.x);
        //delete(this);

    if(!this->isAlive());
        //Destroy boar
}
void Boar::stun() {

    is_stunned = true;
    stun_timer = 100;
}
