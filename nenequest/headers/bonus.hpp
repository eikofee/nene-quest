#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

#include "entity.hpp"

enum BonusType { BONUS_HP, BONUS_WEAPON };

class Bonus : public Entity {
   public:
    Bonus();
    virtual ~Bonus();
    BonusType getBonusType();
    virtual EntityType getEntityType();

   protected:
    BonusType bonus_type;

   private:
};

#endif  // BONUS_H
