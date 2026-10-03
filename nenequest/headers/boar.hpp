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

   protected:
   private:
    static const int BOAR_DAMAGE = 1;
    static constexpr float STUN_DURATION = 1.f;     // Seconds
    static constexpr float ANIMATION_DELAY = 0.1f;  // Seconds
    static constexpr float BOAR_SPEED = 300.f;      // Pixels/second

    bool is_stunned = false;
    float stun_timer = 0.f;
    void progressAnimation();
};

#endif  // BOAR_HPP
