#include <flame.hpp>
#include <stdio.h>
#include <math.h>
using namespace sf;

Flame::Flame()
{
    //ctor
}

Flame::Flame(Vector2f position, float f, float g_depth, bool straightLine){
    straight_line = straightLine;
    depth = g_depth;
    initial_location = position;
    fact = f;

	texture.loadFromFile("img/icon_fire.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(position);
    if(!straightLine)
        sprite.scale(0.5,0.5);
    else
        sprite.scale(0.7,0.7);

    updateAutoHitboxSize();
	sf::RectangleShape* hitbox = new sf::RectangleShape();
    hitbox->setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	hitboxes.push_back(hitbox);
	updateAutoHitboxPosition();

	speed = Vector2f(-2.7,1);

}

void Flame::update(float elapsedTime){

    lifespan += elapsedTime;
    if(!straight_line){
        //Make the flame follow a curve
        this->setPosition(this->getPosition().x + elapsedTime*speed.x/6.5,initial_location.y + fact*1.4 *sin(lifespan/(600)));

        //Make the flame smaller when it goes up (when it's derivative (cos) is < 0 and bigger when it goes down
        if(cos(lifespan/(600)) > 0 && sprite.getScale().x <= 1){
            hitboxes.at(0)->setScale(sprite.getScale().x + 0.01, sprite.getScale().y + 0.01);
            sprite.setScale(sprite.getScale().x + 0.01, sprite.getScale().y + 0.01);
        }
        else{
            span_left += elapsedTime;
			hitboxes.at(0)->setScale(sprite.getScale().x - 0.01, sprite.getScale().y - 0.01);
            sprite.setScale(sprite.getScale().x - 0.01, sprite.getScale().y - 0.01);
        }
        //Begin a timer when the flame begin to go up to make it disappear
        if(span_left > 400)
            is_dead = true;
    }
    else{
        float sp = -0.8  *(1000-lifespan)/1000;
        this->setPosition(this->getPosition().x + elapsedTime*sp/6.5, initial_location.y -abs(this->getPosition().x-initial_location.x) *tan(fact*3.1415/180));

        if(sprite.getScale().x < 1)
            sprite.setScale(sprite.getScale().x+ 0.01,sprite.getScale().y+ 0.01);

        if(lifespan > 1000)
            is_dead = true;
        }

}

bool Flame::isDead(){
    return is_dead;
}

Flame::~Flame()
{
    //dtor
}
