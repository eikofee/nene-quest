#include "../headers/enemy.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

Enemy::Enemy(){

}

Enemy::~Enemy() {
    //dtor
}

short int Enemy::getAttackDamage(){
    return attack_damage;
}

 void Enemy::update(float elapsedTime){

    this->move(elapsedTime);
 }
