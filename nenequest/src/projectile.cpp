#include "../headers/projectile.hpp"

Projectile::Projectile()
{
    //ctor
}

Projectile::~Projectile()
{
    //dtor
}

float Projectile::getDepth(){
    return depth ;
}


float Projectile::getDrawDepth(){
    return depth + Entity::DEPTH_DIFF;
}
