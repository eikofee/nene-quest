#ifndef ITEMWEAPON_H
#define ITEMWEAPON_H


#include "../headers/movableEntity.hpp"
#include "../headers/weaponType.hpp"
#include <SFML/Graphics.hpp>


class ItemWeapon : public MovableEntity
{
    public:
        ItemWeapon(WeaponType type, sf::Vector2f position);
        virtual ~ItemWeapon();
        WeaponType getWeaponType();

    protected:

    private:
        WeaponType weapon_type;
};

#endif // ITEMWEAPON_H
