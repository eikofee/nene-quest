#include "../headers/../headers/livingEntity.hpp"

LivingEntity::LivingEntity(int life)
{
    this->hp = life;
}

bool LivingEntity::isAlive()
{
    return this->hp >= 1;
}

int LivingEntity::getHp()
{
    return this->hp;
}
