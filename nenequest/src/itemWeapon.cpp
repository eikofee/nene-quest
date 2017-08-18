#include "../headers/itemWeapon.hpp"

using namespace sf;

ItemWeapon::ItemWeapon(short int weaponType, Vector2f position) {

    switch (weaponType) {
        case SWORD:
            texture.loadFromFile("img/icon_sword.png");
            sprite.setTexture(texture);
            break;
        case AXE:
            texture.loadFromFile("img/obj_barrel.png");
            sprite.setTexture(texture);
            break;
        case BOW:
            texture.loadFromFile("img/obj_barrel.png");
            sprite.setTexture(texture);
            break;
        default:
            break;
    }

    weapon_type = weaponType;
    this->setPosition(position.x, position.y);
}

ItemWeapon::~ItemWeapon() {
    //dtor
}

short int ItemWeapon::getWeaponType(){
    return weapon_type;
}
