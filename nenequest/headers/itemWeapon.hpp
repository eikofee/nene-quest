#ifndef ITEMWEAPON_H
#define ITEMWEAPON_H

#include <SFML/Graphics.hpp>

#include "bonus.hpp"
#include "weaponType.hpp"

enum ItemWeaponType { ITEM_AXE, ITEM_SWORD, ITEM_GREATSWORD, ITEM_BOW };

class ItemWeapon : public Bonus {
   public:
    ItemWeapon(WeaponType type, sf::Vector2f position);
    virtual ~ItemWeapon();
    WeaponType getWeaponType();
    void setWeaponType(WeaponType type);
    virtual void update(float elapsedTime);
    bool isPickable();
    void isJustDropped();

   protected:
   private:
    static constexpr float COOLDOWN_BETWEEN_PICKUP = 1.5;
    WeaponType weapon_type;
    float unpickableTimer = COOLDOWN_BETWEEN_PICKUP;
};

#endif  // ITEMWEAPON_H
