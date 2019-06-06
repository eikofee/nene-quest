#include "bonusHp.hpp"

using namespace sf;

BonusHp::BonusHp(BonusHpType bonusType, Vector2f position) {
    sf::RectangleShape *zhitbox = new sf::RectangleShape();
    sf::RectangleShape *hitbox = new sf::RectangleShape();

    switch (bonusType) {
        case BONUS_ONIGIRI:
            bonus_type = BONUS_HP;
            texture.loadFromFile("img/item_onigiri.png");
            sprite.setTexture(texture);
            hitbox->setPosition(position);
            hitbox->setSize(Vector2f(sprite.getLocalBounds().width * 0.55,
                                     sprite.getLocalBounds().height * 0.5));
            hitbox->setFillColor(sf::Color(255, 0, 0, 128));
            hitboxes.push_back(hitbox);

            zhitbox->setSize(
                Vector2f(Vector2f(sprite.getLocalBounds().width * 0.55,
                                  sprite.getLocalBounds().height * 0.5)));
            zhitbox->setOrigin(0, 0);
            zhitbox->setPosition(position);
            zhitbox->setFillColor(sf::Color(0, 0, 255, 128));
            zHitboxes.push_back(zhitbox);

            sprite.setOrigin(sprite.getGlobalBounds().width * 0.25,
                             sprite.getGlobalBounds().height * 0.3);
            updateAutoSpritePosition();

            healed_amount = ONIGIRI_HEALED_AMOUNT;
            break;
        default:
            break;
    }
}

BonusHp::~BonusHp() {
    // dtor
}

short int BonusHp::getHealedAmount() { return healed_amount; }
