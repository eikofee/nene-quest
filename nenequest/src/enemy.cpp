#include "../headers/enemy.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

//need to initialize hp and stuff
Enemy::Enemy(int hp) : Entity () {}

Enemy::~Enemy() {
    //dtor
}

short int Enemy::getAttackDamage(){
    return attack_damage;
}

 void Enemy::update(float elapsedTime){

    //this->move(elapsedTime);
 }

 EnemyType Enemy::getEnemyType(){
    return enemy_type;
 }

 bool Enemy::isDead(){
    return is_dead;
 }

 bool Enemy::isDying() {
	 return this->hp < 0; //idk
 }
