#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "arrow.hpp"
#include "entity.hpp"
#include "itemWeapon.hpp"
#include "lifebar.hpp"
#include "weapon.hpp"

class Player : public Entity {
   public:
    Player(std::unique_ptr<Weapon> weapon, sf::Vector2f position,
           bool secondPlayer = false);

    // Weapon
    Weapon *getWeapon();
    std::vector<Arrow *> getArrows();
    void attack();
    void fireArrow();
    void equip(std::unique_ptr<Weapon> w);
    void update(float elapsedTime) override;
    bool isAttacking();
    // True the first time an entity is hit during the current attack
    bool hitOnce(Entity *entity);

    // Life management
    void isHit(int damage);

    // override
    void draw(
        sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates::Default) const override;
    void move(sf::Vector2f g_speed) override;
    void setPosition(float x, float y) override;
    EntityType getEntityType() override;
    virtual PlayerID getId();
    void alterHealth(int value, bool relative) override;

    bool moving_up = false;
    bool moving_down = false;
    bool moving_left = false;
    bool moving_right = false;

    bool isShooting();
    void setShootingState(bool state);

    static constexpr int PLAYER_MAX_HP = 100;


   private:
    static constexpr float PLAYER_SPEED = 500.f;
    static constexpr float INVULNERABILITY_DURATION = 1.f;


    bool is_attacking = false;
    bool animation_state = false;
    bool is_shooting = false;
    float attackTime = 0.1f;
    float currentAttackTime = 0.f;
    std::vector<Entity *> hit_during_attack;
    float currentInvulnerabilityTime = 0.f;

    // Weapon placement
    int weaponXOffset;
    int weaponYOffset;
    int weaponXOffsetVariation;
    int weaponYOffsetVariation;

    sf::Vector2f speed = sf::Vector2f(-10, 0);
    std::vector<std::unique_ptr<Arrow>> arrows;
    sf::Clock clock;
    static constexpr float ANIMATION_DELAY = 0.1f;
    void update_animation();
    void manageMovements();
    sf::Vector2f fixMovements(sf::Vector2f movement);
    void fixPosition();

    void cleanArrows(float elapsedTime);
    PlayerID id;
    std::unique_ptr<Weapon> weapon;
};

#endif
