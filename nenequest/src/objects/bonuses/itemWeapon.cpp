#include <itemWeapon.hpp>

using namespace sf;

ItemWeapon::ItemWeapon(WeaponType type, Vector2f position) {

    this->hitbox_zHitbox_yRatio = 0.5;

    weapon_type = type;
    bonus_type = BONUS_WEAPON;

    texture.loadFromFile(getWeaponPath(type));
    sprite.setTexture(texture);

    sprite.setPosition(position);

    RectangleShape* hitbox = new RectangleShape();
    hitbox->setFillColor(sf::Color(255, 0, 0, 128));
    hitboxes.push_back(hitbox);
    updateAutoHitboxSize();
    updateAutoHitboxPosition();

    RectangleShape* zhitbox = new RectangleShape(Vector2f(hitboxes.at(0)->getSize().x, hitboxes.at(0)->getSize().y*hitbox_zHitbox_yRatio));
    zhitbox->setOrigin(0, -hitboxes.at(0)->getSize().y*(1-hitbox_zHitbox_yRatio));
    zhitbox->setPosition(position);
    zhitbox->setFillColor(sf::Color(0, 0, 255, 128));
    zHitboxes.push_back(zhitbox);
}

ItemWeapon::~ItemWeapon() {
    //dtor
}

WeaponType ItemWeapon::getWeaponType(){
    return weapon_type;
}

void ItemWeapon::setWeaponType(WeaponType type){
    weapon_type = type;

    texture.loadFromFile(getWeaponPath(type));
    this->sprite = Sprite(texture);
    sprite.setPosition(this->getPosition());

    updateAutoHitboxSize();
    updateAutoHitboxPosition();

    zHitboxes.at(0)->setSize(Vector2f(hitboxes.at(0)->getGlobalBounds().width, hitboxes.at(0)->getGlobalBounds().height*hitbox_zHitbox_yRatio));
    zHitboxes.at(0)->setOrigin(0, -hitboxes.at(0)->getSize().y*(1-hitbox_zHitbox_yRatio));
    zHitboxes.at(0)->setPosition(this->getPosition());
}

void ItemWeapon::update(float elapsedTime){
    this->unpickableTimer -= elapsedTime;
}

bool ItemWeapon::isPickable(){
    return unpickableTimer <= 0;
}

void ItemWeapon::isJustDropped(){
    unpickableTimer = COOLDOWN_BETWEEN_PICKUP;
}
