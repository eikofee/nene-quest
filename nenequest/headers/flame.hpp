#ifndef FLAME_H
#define FLAME_H

#include <SFML/Graphics.hpp>

#include "projectile.hpp"

class Flame : public Projectile {
   public:
    static int const FLAMES_DAMAGE = 1;
    Flame();
    Flame(sf::Vector2f position, float f, float g_depth,
          bool straightLine = false);
    virtual ~Flame();
    void update(float elapsedTime) override;

   private:
    // Curved flames, breathed by the living dragon
    static float constexpr CURVE_SPEED = -415.f;         // Pixels/second
    static float constexpr CURVE_PERIOD = 0.6f;          // Seconds per radian
    static float constexpr CURVE_FADE_DURATION = 0.4f;   // Seconds
    // Straight flames, breathed by the dying dragon
    static float constexpr LINE_SPEED = -123.f;          // Pixels/second
    static float constexpr LINE_DURATION = 1.f;          // Seconds
    static float constexpr GROWTH_SPEED = 0.6f;          // Scale/second

    float span_left = 0.f;
    float lifespan = 0.f;
    float fact;
    sf::Vector2f initial_location;
    bool straight_line;
};

#endif  // FLAME_H
