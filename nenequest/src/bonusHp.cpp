#include "../headers/bonusHp.hpp"

using namespace sf;

BonusHp::BonusHp(short int bonusType, Vector2f position) {

    switch (bonusType) {
        case ONIGIRI:
            bonus_type = Item_Onigiri;
            texture.loadFromFile("img/item_onigiri.png");
            sprite.setTexture(texture);

            healed_amount = 10;
            break;
        default:
            break;
    }

    this->setPosition(position.x, position.y);
}

BonusHp::~BonusHp() {
    //dtor
}

short int BonusHp::getHealedAmount(){
    return healed_amount;
}
