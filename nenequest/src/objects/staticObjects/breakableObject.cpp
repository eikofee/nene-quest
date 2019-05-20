#include "breakableObject.hpp"

#include "bonusHp.hpp"
#include "itemWeapon.hpp"

using namespace sf;

BreakableObject::BreakableObject(ObjectType o, Vector2f position) {
    object_type = o;

    getObjectTexture(o);

    sprite.setTexture(texture);

    sf::RectangleShape *hitbox = new sf::RectangleShape();
    hitbox->setFillColor(sf::Color(255, 0, 0, 128));
    hitbox->setPosition(position);
    hitboxes.push_back(hitbox);
    updateAutoHitboxSize();

    sf::RectangleShape *zhitbox = new sf::RectangleShape();
    zhitbox->setFillColor(sf::Color(0, 0, 255, 128));
    zhitbox->setSize(Vector2f(hitboxes.at(0)->getSize().x,
                              hitboxes.at(0)->getSize().y * 0.5));
    zhitbox->setOrigin(0, -hitboxes.at(0)->getSize().y * 0.5);
    zhitbox->setPosition(position);
    zHitboxes.push_back(zhitbox);

    updateAutoSpritePosition();
}

BreakableObject::~BreakableObject() {
    // dtor
}

void BreakableObject::getObjectTexture(ObjectType o) {
    if (o == Chest)
        texture.loadFromFile("img/obj_chest.png");
    else if (o == Barrel)
        texture.loadFromFile("img/obj_barrel.png");
}

Bonus *BreakableObject::getDrops() {
    Bonus *bonus = nullptr;

    switch (rand() % 2) {
        case BONUS_HP:
            bonus = new BonusHp(BONUS_ONIGIRI, this->getPosition());
            break;
        case BONUS_WEAPON:
            switch (rand() % 4) {
                case ITEM_AXE:
                    bonus = new ItemWeapon(Axe, this->getPosition());
                    break;
                case ITEM_SWORD:
                    bonus = new ItemWeapon(Sword, this->getPosition());
                    break;
                case ITEM_GREATSWORD:
                    bonus = new ItemWeapon(GreatSword, this->getPosition());
                    break;
                case ITEM_BOW:
                    bonus = new ItemWeapon(Bow, this->getPosition());
                    break;
            }
    }

    if (object_type == Chest)
        return bonus;
    else if (object_type == Barrel && rand() % 10 < BARREL_DROP_CHANCE)
        return bonus;
    return NULL;
}

EntityType BreakableObject::getEntityType() { return SOLID; }
