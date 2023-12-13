#include "enemy.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

// need to initialize hp and stuff
Enemy::Enemy(int hp) : Entity() { this->hp = hp; }

Enemy::~Enemy() {
    // dtor
}

short int Enemy::getAttackDamage() { return attack_damage; }

void Enemy::update(float elapsedTime) {
    // this->move(elapsedTime);
}

EnemyType Enemy::getEnemyType() { return enemy_type; }

bool Enemy::isDying() {
    return false; // Write down a special animation when an ennemy die
}

EntityType Enemy::getEntityType() { return ENEMY; }
