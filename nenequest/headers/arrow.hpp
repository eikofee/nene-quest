#ifndef ARROW_HPP
#define ARROW_HPP

#include "projectile.hpp"

class Arrow : public Projectile {
   public:
    static int const ARROW_DAMAGE = 1;
    Arrow(sf::Vector2f position, float g_depth);
    virtual ~Arrow();
    void update(float elapsedTime);
    bool isDead();
    void kill();
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default);

   protected:
   private:
    bool is_dead = false;
    bool is_dying = false;
    float lifespan = 0.f;
    float gravity = 80.f;
    float curveTime = 1.f;
    float currentCurveTime = -4.f;
    float highDeadzoneStart = 0.33f;
    float highDeadzoneEnd = 0.66f;

    sf::Texture damage_texture;
    sf::Sprite damage_sprite;
    sf::Vector2f initial_location;
};

#endif  // ARROW_HPP
