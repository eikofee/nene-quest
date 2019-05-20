#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.hpp"

class Projectile : public Entity {
   public:
    Projectile();
    virtual ~Projectile();
    virtual float getDepth();
    virtual float getDrawDepth();

   protected:
    float depth;

   private:
};

#endif  // PROJECTILE_H
