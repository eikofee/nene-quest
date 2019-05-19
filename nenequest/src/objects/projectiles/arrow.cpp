#define _USE_MATH_DEFINES


#include "arrow.hpp"
#include <math.h>

using namespace sf;

float curveCappedValue = 0.2f;
Arrow::Arrow(Vector2f position, float g_depth)
{
    depth = g_depth;
    initial_location = position;
    lifespan = 0;

	texture.loadFromFile("img/weapon_arrow.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/1.5);
    sprite.setPosition(position);

	sf::RectangleShape* hitbox = new sf::RectangleShape();
	hitbox->setFillColor(sf::Color(255, 0, 0, 128));
	hitbox->setPosition(position);
    hitbox->setSize(Vector2f(texture.getSize().x/5, texture.getSize().y/1.8));
    hitbox->setOrigin(0, texture.getSize().y/2 );
	this->hitboxes.push_back(hitbox);

	sf::RectangleShape* zh = new sf::RectangleShape();
	zh->setFillColor(sf::Color(0, 0, 255, 128));
	zh->setSize(Vector2f(texture.getSize().x / 5, texture.getSize().y / 1.8));
	zh->setPosition(position);
	zh->setOrigin(0, texture.getSize().y / 2);
	this->zHitboxes.push_back(zh);

	updateAutoHitboxPosition();

	//speed = Vector2f(0.8,-0.8);
	speed = Vector2f(800, -200);

	damage_texture.loadFromFile("img/icon_damage.png");
	damage_sprite.setTexture(damage_texture);
	damage_sprite.setOrigin(-30, 90);
	damage_sprite.setScale(0.7,0.7);

	currentCurveTime = curveCappedValue;
}

Arrow::~Arrow()
{
    //dtor
}

void Arrow::update(float elapsedTime){

    if(!is_dying){
        lifespan += elapsedTime;

        //Make the arrow follow a curve
       /* this->setPosition(initial_location.x + lifespan*speed.x,initial_location.y + lifespan*speed.y + gravity*lifespan/2);
        sprite.setRotation(atan((speed.y + gravity*lifespan)/speed.x)*180/3.1415);
        hitboxes.at(0)->setRotation(sprite.getRotation());
        if(this->getPosition().y > initial_location.y)
            is_dead = true;
    */
		
		this->setPosition(initial_location.x + speed.x * lifespan, initial_location.y + speed.y * (sin((lifespan / curveTime) * M_PI) /*+ sin(curveCappedValue * M_PI)*/));
		zHitboxes.at(0)->setPosition(getPosition().x, initial_location.y);
		sprite.setRotation(- 30 + lifespan * 60);		// rotation start + (rotation end - rotation start) 
		hitboxes.at(0)->setRotation(sprite.getRotation());
		if (lifespan >= highDeadzoneStart * curveTime && lifespan <= highDeadzoneEnd * curveTime)
			zHitboxes.at(0)->setFillColor(sf::Color(255, 128, 255, 128));	//pink
		else
			zHitboxes.at(0)->setFillColor(sf::Color(0, 0, 255, 128));	//blue

		if (lifespan >= curveTime)
			is_dead = true;
	}
    else{
        if(lifespan > 0)
            lifespan = 0;
        lifespan-= elapsedTime;

        if(lifespan < -150)	//???
            is_dead = true;
    }
}

bool Arrow::isDead(){
    return is_dead;
}

void Arrow::kill(){
    this->depth = 8000;
    damage_sprite.setRotation(hitboxes.at(0)->getRotation());
    damage_sprite.setPosition(hitboxes.at(0)->getPosition().x, hitboxes.at(0)->getPosition().y);
    is_dying = true;
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) {

    //target.draw(hitbox, states);
    target.draw(sprite, states);

    if(is_dying)
        target.draw(damage_sprite, states);

}
