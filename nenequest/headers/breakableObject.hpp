#ifndef BREAKABLEOBJECT_H
#define BREAKABLEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../headers/movableEntity.hpp"
#include "../headers/bonus.hpp"


enum ObjectType {Chest, Barrel};

class BreakableObject : public MovableEntity
{
    public:
        BreakableObject(ObjectType o, sf::Vector2f position);
        virtual ~BreakableObject();
        Bonus* getDrops();

    protected:

    private:
        void getObjectTexture(ObjectType o);
        ObjectType object_type;
};

#endif // BREAKABLEITEM_H
