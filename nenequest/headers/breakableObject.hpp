#ifndef BREAKABLEOBJECT_H
#define BREAKABLEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../headers/movableEntity.hpp"
#include "../headers/bonus.hpp"


enum ObjectType {Chest, Barrel};

class BreakableObject : public Entity
{
    public:
        BreakableObject(ObjectType o, sf::Vector2f position);
        virtual ~BreakableObject();
        Bonus* getDrops();

    protected:

    private:
        static const int BARREL_DROP_CHANCE = 8; //Chances out of 10
        void getObjectTexture(ObjectType o);
        ObjectType object_type;
};

#endif // BREAKABLEITEM_H
