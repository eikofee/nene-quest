#include "../headers/boar.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Boar::Boar(Vector2f position) : Enemy (BOAR_HP) {

    attack_damage = BOAR_DAMAGE;
    enemy_type = Enemy_Boar;

	texture.loadFromFile("img/enemy_boar_anim.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,texture.getSize().x,texture.getSize().y/2));

    hitbox.setPosition(position);
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width*0.8, sprite.getLocalBounds().height*0.5));

	sprite.setOrigin(sprite.getGlobalBounds().width *0.07,sprite.getGlobalBounds().height*0.3 );
    updateSpritePosition();

	speed = Vector2f(-BOAR_SPEED, 0);

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

 void Boar::update(float elapsedTime, Vector2u windowSize) {


    //Move the boar if it isn't stunned
    if(!is_stunned){
        this->move(elapsedTime);
        if(clock.getElapsedTime().asSeconds() > ANIMATION_DELAY){
            progressAnimation();
            clock.restart();
     }

    }
    else{
        stun_timer -= elapsedTime;
        if(stun_timer <= 0)
            is_stunned = false;
    }

    if(!this->isOnScreen(windowSize) || !this->isAlive())
        is_dead = true;
}

void Boar::stun() {

    is_stunned = true;
    stun_timer = STUN_DURATION;
}
