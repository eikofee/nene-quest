#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "randomShape.hpp"

class Background : public sf::Drawable, sf::Transformable {
   private:
    sf::RectangleShape sky;
    sf::RectangleShape ground;
    sf::Vector2u v;

    // Spawn intervals are in pixels scrolled
    static const int CLOUD_SPAWN_INTERVAL = 500;
    static const int CLOUD_SPAWN_INTERVAL_RANDOM = 200;
    static const int MOUNTAIN_SPAWN_INTERVAL = 200;
    static const int MOUNTAIN_SPAWN_INTERVAL_RANDOM = 100;
    static const int CLOUD_SPAWN_Y_TOP = 0;
    static const int CLOUD_SPAWN_Y_BOTTOM = 200;
    static const int MOUNTAIN_VAR_Y_OFFSET = 30;

    float cloudSpeedModifier = 1.0f;
    float mountainSpeedModifier = 1.5f;
    static constexpr float DRIFT_SPEED = 60.f;  // Pixels/second, even when not scrolling
    float scrollSpeed = 0.f;                    // Pixels/second

    std::vector<RandomShape *> clouds;
    std::vector<RandomShape *> mountains;
    float nextCloud = 0.f;
    float nextMountain = 0.f;
    float cloudDistance = 0.f;     // Pixels scrolled since the last cloud
    float mountainDistance = 0.f;  // Pixels scrolled since the last mountain

   public:
    Background(sf::Vector2u v);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(this->sky);
        for (auto rc : this->clouds) target.draw(*rc);

        for (auto rm : this->mountains) target.draw(*rm);

        target.draw(this->ground);
    }

    virtual void setPosition(float x, float y) {
        this->sky.setPosition(x, y);
        this->ground.setPosition(x, y);
    }
    float getSkyHeight();

    void update(float elapsedTime);  // Seconds
    void createClouds();
    void createMountains();
    void setSpeed(float speed);
};

#endif
