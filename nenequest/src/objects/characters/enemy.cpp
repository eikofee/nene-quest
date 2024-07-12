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
    this->currentInvulnerabilityTime -= elapsedTime;
    // this->move(elapsedTime);
}

EnemyType Enemy::getEnemyType() { return enemy_type; }

bool Enemy::isDying() {
    return false; // Write down a special animation when an ennemy die
}

EntityType Enemy::getEntityType() { return ENEMY; }

void Enemy::stun() { }

float Enemy::getInvunerabilityDuration(EnemyType t) {
    switch (t) {
        case Enemy_Dragon:
            return Enemy::DRAGON_INVULNERABILITY_TIME;
        case Enemy_Boar:
            return Enemy::BOAR_INVULNERABILITY_TIME;
    }
    return -1; // can't happen
}


void Enemy::alterHealth(int value, bool relative) {
    if(currentInvulnerabilityTime < 0){
        if (relative)
            health += value;
        else
            health = value;
        currentInvulnerabilityTime = this->getInvunerabilityDuration(this->getEnemyType());
    }
}

