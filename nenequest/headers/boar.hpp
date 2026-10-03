#ifndef BOAR_HPP
#define BOAR_HPP

#include <SFML/Graphics.hpp>

#include "enemy.hpp"

class Boar : public Enemy {
   public:
    Boar(sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Boar();
    void update(float elapsedTime) override;
    void stun() override;
    // Knocked out once its health is gone, then it's dead
    bool isDying() override;
    bool isDead() override;

   protected:
   private:
    static const int BOAR_DAMAGE = 1;
    static constexpr float STUN_DURATION = 1.f;     // Seconds
    static constexpr float ANIMATION_DELAY = 0.1f;  // Seconds
    static constexpr float BOAR_SPEED = 300.f;      // Pixels/second
    // Dying: knocked back with a hop while flipping over, then it blinks
    static constexpr float HOP_DURATION = 0.5f;       // Seconds
    static constexpr float HOP_HEIGHT = 80.f;         // Pixels
    static constexpr float KNOCKBACK_SPEED = 250.f;   // Pixels/second
    static constexpr float DYING_DURATION = 1.2f;     // Seconds, hop included
    static constexpr float BLINK_DELAY = 0.08f;       // Seconds

    bool is_stunned = false;
    float stun_timer = 0.f;
    float dying_timer = 0.f;
    bool dying_started = false;
    sf::Vector2f dying_position;  // Of the sprite, when it was knocked out
    void animateDeath(float elapsedTime);
    void progressAnimation();
};

#endif  // BOAR_HPP
