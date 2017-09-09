#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>
#include "../headers/movableEntity.hpp"

enum BonusType {Item_Axe, Item_Sword, Item_Greatsword, Item_Bow, Item_Onigiri, Number_of_Bonuses = 5, Item_Random, Item_None};

class Bonus : public MovableEntity
{
    public:
        Bonus();
        virtual ~Bonus();
        BonusType getBonusType();

    protected:
        BonusType bonus_type;

    private:
};

#endif // BONUS_H
