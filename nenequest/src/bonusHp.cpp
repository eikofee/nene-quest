#include "../headers/bonusHp.hpp"
#include "../headers/config.hpp"

using namespace sf;

BonusHp::BonusHp(short int bonusType, Vector2f position) {

    switch (bonusType) {
        case ONIGIRI:
            bonus_type = Item_Onigiri;
            texture.loadFromFile(GSP_ITEM_ONIGIRI);
            sprite.setTexture(texture);

            hitbox.setPosition(position);
            hitbox.setSize(Vector2f(sprite.getLocalBounds().width *0.55, sprite.getLocalBounds().height*0.5));

            sprite.setOrigin(sprite.getGlobalBounds().width*0.25,sprite.getGlobalBounds().height*0.3 );
            updateSpritePosition();


            healed_amount = ONIGIRI_HEALED_AMOUNT;
            break;
        default:
            break;
    }
}

BonusHp::~BonusHp() {
    //dtor
}

short int BonusHp::getHealedAmount(){
    return healed_amount;
}
