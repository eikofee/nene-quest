#define _USE_MATH_DEFINES


#include <arrow.hpp>
#include <math.h>

using namespace sf;

Arrow::Arrow(Vector2f position, float g_depth)
{
    depth = g_depth;
    initial_location = position;
    lifespan = 0;

	texture.loadFromFile("img/weapon_arrow.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/1.5);
    sprite.setPosition(position);

    hitbox.setSize(Vector2f(texture.getSize().x/5, texture.getSize().y/1.8));
    hitbox.setOrigin(0, texture.getSize().y/2 );
    updateHitboxPosition();

	speed = Vector2f(0.8,-0.8);

	damage_texture.loadFromFile("img/icon_damage.png");
	damage_sprite.setTexture(damage_texture);
	damage_sprite.setOrigin(-30, 90);
	damage_sprite.setScale(0.7,0.7);
}

Arrow::~Arrow()
{
    //dtor
}

void Arrow::update(float elapsedTime){

    if(!is_dying){
        lifespan += elapsedTime;

        //Make the arrow follow a curve
        this->setPosition(initial_location.x + lifespan*speed.x,initial_location.y + lifespan*speed.y + gravity*lifespan*lifespan/2);
        sprite.setRotation(atan((speed.y + gravity*lifespan)/speed.x)*180/3.1415);
        hitbox.setRotation(sprite.getRotation());

        if(this->getPosition().y > initial_location.y)
            is_dead = true;
    }
    else{
        if(lifespan > 0)
            lifespan = 0;
        lifespan-= elapsedTime;

        if(lifespan < -150)
            is_dead = true;
    }
}

bool Arrow::isDead(){
    return is_dead;
}

void Arrow::kill(){
    this->depth = 8000;
    damage_sprite.setRotation(hitbox.getRotation());
    damage_sprite.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
    is_dying = true;
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) {

    //target.draw(hitbox, states);
    target.draw(sprite, states);

    if(is_dying)
        target.draw(damage_sprite, states);

}
