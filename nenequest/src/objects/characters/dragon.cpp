#include "dragon.hpp"

#include <time.h>

#include <algorithm>

#include "flame.hpp"
#include "game.hpp"

using namespace sf;
using namespace std;

Dragon::Dragon(Vector2f position) : Enemy(DRAGON_HP) {
    srand(time(NULL));

    attack_damage = DRAGON_DAMAGE;
    enemy_type = Enemy_Dragon;

    flame_timer = 0;

    texture.loadFromFile("img/enemy_dragon.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, texture.getSize().y / 2,
                                  texture.getSize().x / 2,
                                  texture.getSize().y / 2));
    sprite.setPosition(position);

    sf::RectangleShape *hitbox = new sf::RectangleShape();
    hitbox->setPosition(position);
    hitbox->setSize(Vector2f(sprite.getLocalBounds().width,
                             sprite.getLocalBounds().height));
    hitbox->setFillColor(Color(255, 0, 0, 128));
    hitboxes.push_back(hitbox);

    sf::RectangleShape *zhitbox = new sf::RectangleShape();
    zhitbox->setSize(Vector2f(sprite.getLocalBounds().width * 0.8,
                              sprite.getLocalBounds().height * 0.4));
    zhitbox->setOrigin(-sprite.getLocalBounds().width * 0.2,
                       -sprite.getLocalBounds().height * 0.6);
    zhitbox->setPosition(position);
    zhitbox->setFillColor(Color(0, 0, 255, 128));
    zHitboxes.push_back(zhitbox);

    // Finer hitboxes following the dragon's shape (size, then origin),
    // unused for now:
    //   body  530x120 at (-270, -410)
    //   neck  220x290 at (-270, -120)
    //   head  310x180 at (-50, -30)

    updateAutoSpritePosition();

    speed = Vector2f(DRAGON_SPEED, 0);
}


void Dragon::update(float elapsedTime) {
    if (!this->isDying()) {
        // Move dragon back and forth
        movement_timer += elapsedTime;
        if (movement_timer > MOVEMENT_DURATION) {
            speed = Vector2f(-speed.x, speed.y);
            movement_timer = 0;
        }

        this->move(computeMove(elapsedTime));

        // Breathe fire
        flame_timer += elapsedTime;
        if (fire_breathing) {
            if (flame_timer > DELAY_BETWEEN_FLAMES) {
                flames.push_back(make_unique<Flame>(
                    Vector2f(
                        sprite.getPosition().x - sprite.getOrigin().x + 100,
                        sprite.getPosition().y - sprite.getOrigin().y + 100 +
                            (float)(rand() % 100)),
                    70 + (float)(rand() % 130), this->getDepth()));
                flame_timer = 0;
            }
        }
    }
    // Dying animation
    else {
        fire_breathing = true;
        // Delete the hitbox at the start of the dying animation
        if (!dying_started) {
            for (unsigned int i = 1; i < hitboxes.size(); i++)
                hitboxes.at(i)->setSize(Vector2f(0, 0));
            sprite.setOrigin(350, 400);
            sprite.move(350, 400);
            dying_started = true;
            movement_timer = 0;
            speed = Vector2f(DEAD_SHAKE_SPEED, DEAD_SHAKE_SPEED);
            flame_timer = DEAD_DELAY_BETWEEN_FLAMES;  // First flame right away
        } else if (dying_timer < DEAD_ANIMATION_DURATION) {
            dying_timer += elapsedTime;
            if (sprite.getRotation() < 90)
                sprite.setRotation(90 * dying_timer / DEAD_ANIMATION_DURATION *
                                   6);
            else {
                sprite.move(computeMove(elapsedTime));
                movement_timer += elapsedTime;
                if (movement_timer > DEAD_SHAKE_DURATION) {
                    speed.x = -speed.x;
                    movement_timer = 0;
                }
                flame_timer += elapsedTime;
                if (flame_timer > DEAD_DELAY_BETWEEN_FLAMES) {
                    flames.push_back(
                        make_unique<Flame>(Vector2f(sprite.getPosition().x + 270,
                                           sprite.getPosition().y - 150),
                                  70, this->getDepth(), true));
                    flame_timer = 0;
                }
            }
        }
    }
    // Update animation
    if (clock.getElapsedTime().asSeconds() > ANIMATION_DELAY) {
        progressAnimation();
        clock.restart();
    }

    // Delete old flames
    for (auto &flame : flames) flame->update(elapsedTime);
    flames.erase(remove_if(flames.begin(), flames.end(),
                           [](auto &flame) { return flame->isDead(); }),
                 flames.end());
}

void Dragon::progressAnimation() {
    if (fire_breathing) {
        if (animation_state == 0) {
            animation_state = 1;
            sprite.setTextureRect(IntRect(texture.getSize().x / 2, 0,
                                          texture.getSize().x,
                                          texture.getSize().y / 2));
        } else {
            animation_state = 0;
            sprite.setTextureRect(IntRect(0, 0, texture.getSize().x / 2,
                                          texture.getSize().y / 2));
        }
    } else {
        if (animation_state == 0) {
            animation_state = 1;
            sprite.setTextureRect(
                IntRect(texture.getSize().x / 2, texture.getSize().y / 2,
                        texture.getSize().x, texture.getSize().y));
        } else {
            animation_state = 0;
            sprite.setTextureRect(IntRect(0, texture.getSize().y / 2,
                                          texture.getSize().x / 2,
                                          texture.getSize().y));
        }
    }
}

void Dragon::breathFire() {
    flame_timer = 0;
    fire_breathing = !fire_breathing;
}

void Dragon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (Game::IsDebugMode()) {
        for (auto h : hitboxes) target.draw(*h, states);
        for (auto zh : zHitboxes) target.draw(*zh, states);
    }

    target.draw(sprite, states);
}

bool Dragon::isBreatingFire() { return fire_breathing; }

vector<Projectile *> Dragon::getFlames() {
    vector<Projectile *> result;
    for (auto &flame : flames) result.push_back(flame.get());
    return result;
}

sf::Vector2f Dragon::computeMove(float elapsedTime) {
    sf::Vector2f r = Vector2f(speed.x * elapsedTime, speed.y * elapsedTime);
    return r;
}
