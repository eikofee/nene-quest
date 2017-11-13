#ifndef ITEMWEAPON_H
#define ITEMWEAPON_H


#include <bonus.hpp>
#include <weaponType.hpp>
#include <SFML/Graphics.hpp>


class ItemWeapon : public Bonus
{
    public:
        ItemWeapon(WeaponType type, sf::Vector2f position);
        virtual ~ItemWeapon();
        WeaponType getWeaponType();
        bool checkIfDropped();
        void setDropped(bool v);

    protected:

    private:
        WeaponType weapon_type;
        bool is_dropped = false;
};

#endif // ITEMWEAPON_H
