#include "../headers/dragon.hpp"

using namespace sf;
using namespace std;


Dragon::Dragon(int hp, Vector2f position) : Enemy (hp) {

    srand(NULL);

    attack_damage = DRAGON_DAMAGE;
    enemy_type = Enemy_Dragon;

	texture.loadFromFile("img/enemy_dragon.png");
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, texture.getSize().y/2,texture.getSize().x/2, texture.getSize().y/2));

    hitbox.setPosition(position);
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width *0.73, sprite.getLocalBounds().height*0.5));

	sprite.setOrigin(sprite.getGlobalBounds().width*0.27,sprite.getGlobalBounds().height*0.5 );
    updateSpritePosition();

	speed = Vector2f(DRAGON_SPEED,0);

}

Dragon::~Dragon(){
    for(int i = 0;i < flames.size();i++){
        delete(flames.at(i));
    }
}

 void Dragon::update(float elapsedTime){

    if(clock.getElapsedTime().asSeconds() > ANIMATION_DELAY){
        progressAnimation();
        clock.restart();
    }

    //Move dragon back and forth
    movement_timer += elapsedTime;
    if(movement_timer > MOVEMENT_DURATION){

        speed = Vector2f( -speed.x, speed.y);
        movement_timer = 0;
    }
    this->move(elapsedTime);

    //Breathe fire
    flame_timer += elapsedTime;
    if(fire_breathing)
        if(flame_timer > DELAY_BETWEEN_FLAMES){
            flames.push_back(new Flame(Vector2f(sprite.getPosition().x - sprite.getOrigin().x + 100 ,
                                                        sprite.getPosition().y -sprite.getOrigin().y + 100 + (float)(rand()%100) ), 70 + (float)(rand()%130)));
            flame_timer=0;
        }

    //Delete old flames
    for(int i = 0;i < flames.size();i++){
        flames.at(i)->update(elapsedTime);
        if(flames.at(i)->isDead()){
            delete(flames.at(i));
            flames.erase(flames.begin()+i);
        }
    }
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

void Dragon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    //  target.draw(hitbox, states);
    target.draw(sprite, states);

    for(Flame* var : flames)
        target.draw(*var);
}

bool Dragon::isBreatingFire(){
    return fire_breathing;
}

vector<Flame*> Dragon::getFlames(){
    return flames;
}
