#include "../headers/livingEntity.hpp"

LivingEntity::LivingEntity(int hp)
{
    this->hp = hp;
}

bool LivingEntity::isAlive()
{
    return this->hp > 0;
}

void LivingEntity::take_damage(int amount)
{
    this->hp = this->hp - amount;
}
