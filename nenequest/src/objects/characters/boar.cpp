#include "boar.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;

Boar::Boar(Vector2f position) : Enemy(BOAR_HP) {
    hitbox_sprite_xRatio = 0.8;
    hitbox_sprite_yRatio = 0.5;
    hitbox_zHitbox_xRatio = 1;
    hitbox_zHitbox_yRatio = 0.5;

    attack_damage = BOAR_DAMAGE;
    enemy_type = Enemy_Boar;

    texture = &getTexture("img/enemy_boar_anim.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect(
        IntRect(0, 0, texture->getSize().x, texture->getSize().y / 2));

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
        sprite.setTextureRect(IntRect(0, texture->getSize().y / 2,
                                      texture->getSize().x,
                                      texture->getSize().y));
    } else {
        animation_state = 0;
        sprite.setTextureRect(
            IntRect(0, 0, texture->getSize().x, texture->getSize().y / 2));
    }
}

void Boar::update(float elapsedTime) {
    Enemy::update(elapsedTime);  // Counts down the invulnerability
    if (this->isDying()) {
        animateDeath(elapsedTime);
        return;
    }

    // Move the boar if it isn't stunned
    if (!is_stunned) {
        this->move(speed * elapsedTime);
        if (clock.getElapsedTime().asSeconds() > ANIMATION_DELAY) {
            progressAnimation();
            clock.restart();
        }

    } else {
        stun_timer -= elapsedTime;
        if (stun_timer <= 0) is_stunned = false;
    }
}

void Boar::stun() {
    is_stunned = true;
    stun_timer = STUN_DURATION;
}

bool Boar::isDying() { return health <= 0 && dying_timer < DYING_DURATION; }

bool Boar::isDead() {
    return dead || (health <= 0 && dying_timer >= DYING_DURATION);
}

// Only the sprite moves: the hitboxes stay, and a dying boar is harmless
void Boar::animateDeath(float elapsedTime) {
    if (!dying_started) {
        // Spin around its center instead of its feet, without moving
        FloatRect bounds = sprite.getLocalBounds();
        Vector2f center(bounds.width / 2, bounds.height / 2);
        sprite.move(center - sprite.getOrigin());
        sprite.setOrigin(center);
        dying_position = sprite.getPosition();
        dying_started = true;
    }
    dying_timer += elapsedTime;

    if (dying_timer < HOP_DURATION) {
        // Knocked back (it was running left), flipping onto its back
        float progress = dying_timer / HOP_DURATION;
        sprite.setPosition(
            dying_position.x + KNOCKBACK_SPEED * dying_timer,
            dying_position.y - HOP_HEIGHT * sin(progress * M_PI));
        sprite.setRotation(180 * progress);
    } else {
        // Lying on its back, blinking until it's gone
        sprite.setPosition(dying_position.x + KNOCKBACK_SPEED * HOP_DURATION,
                           dying_position.y);
        sprite.setRotation(180);
        bool visible = (int)(dying_timer / BLINK_DELAY) % 2 == 0;
        sprite.setColor(Color(255, 255, 255, visible ? 255 : 0));
    }
}
