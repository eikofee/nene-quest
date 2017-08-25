#include "../headers/enemy.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

Enemy::Enemy(int hp) : LivingEntity (hp) {}

Enemy::~Enemy() {
    //dtor
}

short int Enemy::getAttackDamage(){
    return attack_damage;
}

 void Enemy::update(float elapsedTime, Vector2u windowSize){

    this->move(elapsedTime);
 }

 EnemyType Enemy::getEnemyType(){
    return enemy_type;
 }

 bool Enemy::isDead(){
    return is_dead;
 }
