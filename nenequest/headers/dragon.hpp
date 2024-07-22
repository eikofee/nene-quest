#ifndef DRAGON_H
#define DRAGON_H

#include <SFML/Graphics.hpp>

#include "enemy.hpp"

class Projectile;
class Dragon : public Enemy {
   public:
    Dragon(sf::Vector2f position = sf::Vector2f(0, 0));
    ~Dragon();
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const;  //???
    void update(float elapsedTime);
    void breathFire();
    bool isBreatingFire();
    std::vector<Projectile *> getFlames();  // Should be projectile ?
                                            // void setPosition(int x, int y);
                                            // void move(float elapsedTime);
    // void move(sf::Vector2f g_speed, float elapsedTime);
    // bool detectHit(Entity* entity);

   protected:
   private:
    static int const DRAGON_DAMAGE = 50;
    static int const MOVEMENT_DURATION = 1000;     // Milliseconds
    static int const DELAY_BETWEEN_FLAMES = 100;   // Milliseconds
    static float constexpr ANIMATION_DELAY = 0.5f;  // Seconds
    static float constexpr DRAGON_SPEED = 0.1f;     // Pixels/milliseconds
    static float constexpr DEAD_ANIMATION_DURATION = 6000f;  // Milliseconds

    std::vector<Projectile *> flames;
    sf::Vector2f computeMove(float elapsedTime);

    float movement_timer = 0f;
    bool fire_breathing = false;
    void progressAnimation();
    float flame_timer = 0f;
    float dying_timer = 0f;
};

#endif  // DRAGON_H
