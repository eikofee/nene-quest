#ifndef RANDOMMOUNTAIN_HPP_INCLUDED
#define RANDOMMOUNTAIN_HPP_INCLUDED

#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <list>

#include "randomShape.hpp"

class RandomMountain : public RandomShape {
   private:
    static const int MAX_HEIGHT = 500;
    static const int MIN_HEIGHT = 400;
    static const int RANDOM_ANGLE = 5;

    sf::RectangleShape *body;
    bool alive = true;

   public:
    RandomMountain();
    ~RandomMountain();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(*(this->body));
    }

    virtual void setPosition(float x, float y) {
        this->setPosition(sf::Vector2f(x, y));
    }

    virtual void setPosition(sf::Vector2f v) { this->body->setPosition(v); }

    void update() override;
    bool isAlive() override;
    void translate(float x, float y) override;
};

#endif
