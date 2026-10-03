#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.hpp"

class Projectile : public Entity {
   public:
    Projectile();
    virtual ~Projectile();
    float getDepth() override;

   protected:
    float depth;

   private:
};

#endif  // PROJECTILE_H
