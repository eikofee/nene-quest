#include "../headers/itemWeapon.hpp"

using namespace sf;

ItemWeapon::ItemWeapon(WeaponType type, Vector2f position) {

    weapon_type = type;

    texture.loadFromFile(getWeaponPath(type));
    sprite.setTexture(texture);

    this->setPosition(position.x, position.y);
}

ItemWeapon::~ItemWeapon() {
    //dtor
}

WeaponType ItemWeapon::getWeaponType(){
    return weapon_type;
}
