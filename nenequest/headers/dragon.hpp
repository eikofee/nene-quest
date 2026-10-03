#ifndef DRAGON_H
#define DRAGON_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "enemy.hpp"

#include "projectile.hpp"

class Dragon : public Enemy {
   public:
    Dragon(sf::Vector2f position = sf::Vector2f(0, 0));
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const override;
    void update(float elapsedTime) override;
    void breathFire();
    bool isBreatingFire();
    // Plays its death animation once its health is gone, then it's dead
    bool isDying() override;
    bool isDead() override;
    std::vector<Projectile *> getFlames();

   protected:
   private:
    static int const DRAGON_DAMAGE = 50;
    static float constexpr MOVEMENT_DURATION = 1.f;          // Seconds
    static float constexpr DELAY_BETWEEN_FLAMES = 0.1f;      // Seconds
    static float constexpr FIRE_DURATION = 2.f;              // Seconds
    static float constexpr CALM_DURATION = 3.f;              // Seconds
    static float constexpr ANIMATION_DELAY = 0.5f;           // Seconds
    static float constexpr DRAGON_SPEED = 100.f;             // Pixels/second
    static float constexpr DEAD_ANIMATION_DURATION = 6.f;    // Seconds
    static float constexpr DEAD_SHAKE_SPEED = 180.f;         // Pixels/second
    static float constexpr DEAD_SHAKE_DURATION = 0.04f;      // Seconds
    static float constexpr DEAD_DELAY_BETWEEN_FLAMES = 0.6f; // Seconds

    std::vector<std::unique_ptr<Projectile>> flames;
    sf::Vector2f computeMove(float elapsedTime);

    float movement_timer = 0.f;
    bool fire_breathing = false;
    void progressAnimation();
    float flame_timer = 0.f;
    float breath_timer = 0.f;  // Since it started or stopped breathing fire
    float dying_timer = 0.f;
    bool dying_started = false;
};

#endif  // DRAGON_H
