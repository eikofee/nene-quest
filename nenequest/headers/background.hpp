#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable, sf::Transformable {
    private:
        sf::RectangleShape sky;
        sf::RectangleShape ground;
    public:
        Background(sf::Vector2u v);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(this->sky);
            target.draw(this->ground);
        }

        virtual void setPosition(float x, float y) {
            this->sky.setPosition(x, y);
            this->ground.setPosition(x, y);
        }
};

#endif
