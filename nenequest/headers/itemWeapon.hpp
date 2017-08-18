#ifndef ITEMWEAPON_H
#define ITEMWEAPON_H


#include "../headers/movableEntity.hpp"
#include <SFML/Graphics.hpp>


class ItemWeapon : public MovableEntity
{
    public:
        static const short int SWORD = 1;
        static const short int AXE = 2;
        static const short int BOW = 3;

        ItemWeapon(short int weaponType, sf::Vector2f position);
        virtual ~ItemWeapon();
        short int getWeaponType();

    protected:

    private:
        short int weapon_type;
};

#endif // ITEMWEAPON_H
