#include "boar.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Boar::Boar(Vector2f position) : Enemy(BOAR_HP) {
    hitbox_sprite_xRatio = 0.8;
    hitbox_sprite_yRatio = 0.5;
    hitbox_zHitbox_xRatio = 1;
    hitbox_zHitbox_yRatio = 0.5;

    attack_damage = BOAR_DAMAGE;
    enemy_type = Enemy_Boar;

    texture.loadFromFile("img/enemy_boar_anim.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(
        IntRect(0, 0, texture.getSize().x, texture.getSize().y / 2));

    sf::RectangleShape *hitbox = new sf::RectangleShape();
    hitbox->setPosition(position);
    hitbox->setSize(
        Vector2f(sprite.getLocalBounds().width * hitbox_sprite_xRatio,
                 sprite.getLocalBounds().height * hitbox_sprite_yRatio));
    hitbox->setFillColor(sf::Color(255, 0, 0, 128));
    hitboxes.push_back(hitbox);

    sf::RectangleShape *zhitbox = new sf::RectangleShape();
    zhitbox->setSize(Vector2f(hitbox->getSize().x * hitbox_zHitbox_xRatio,
                              hitbox->getSize().y * hitbox_zHitbox_yRatio));
    zhitbox->setOrigin(0, zhitbox->getSize().y);
    zhitbox->setPosition(position.x, position.y + hitbox->getSize().y);
    zhitbox->setFillColor(sf::Color(0, 0, 255, 128));
    zHitboxes.push_back(zhitbox);

    sprite.setOrigin(sprite.getGlobalBounds().width * 0.07,
                     sprite.getGlobalBounds().height * 0.3);
    updateAutoSpritePosition();

    speed = Vector2f(-BOAR_SPEED, 0);
}

Boar::~Boar() {
    // dtor
}

void Boar::progressAnimation() {
    if (animation_state == 0) {
        animation_state = 1;
        sprite.setTextureRect(IntRect(0, texture.getSize().y / 2,
                                      texture.getSize().x,
                                      texture.getSize().y));
    } else {
        animation_state = 0;
        sprite.setTextureRect(
            IntRect(0, 0, texture.getSize().x, texture.getSize().y / 2));
    }
}

void Boar::update(float elapsedTime) {
    // Move the boar if it isn't stunned
    if (!is_stunned) {
        // this->move(elapsedTime);
        this->move(speed);
        if (clock.getElapsedTime().asSeconds() > ANIMATION_DELAY) {
            progressAnimation();
            clock.restart();
        }

    } else {
        stun_timer -= elapsedTime;
        if (stun_timer <= 0) is_stunned = false;
    }

    // if(!this->isOnScreen(windowSize) || !this->isAlive())
    //    is_dead = true;
}

void Boar::stun() {
    is_stunned = true;
    stun_timer = STUN_DURATION;
}
