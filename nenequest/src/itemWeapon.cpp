#include "../headers/itemWeapon.hpp"

using namespace sf;

ItemWeapon::ItemWeapon(WeaponType type, Vector2f position) {

    weapon_type = type;
    if(type == Sword)
        bonus_type = Item_Sword;
    else if(type == Axe)
        bonus_type = Item_Axe;
    else if(type == Bow)
        bonus_type = Item_Bow;
    else if(type == GreatSword)
        bonus_type = Item_Greatsword;

    texture.loadFromFile(getWeaponPath(type));
    sprite.setTexture(texture);

    updateHitboxSize();
    updateHitboxPosition();

    this->setPosition(position.x, position.y);
}

ItemWeapon::~ItemWeapon() {
    //dtor
}

WeaponType ItemWeapon::getWeaponType(){
    return weapon_type;
}
