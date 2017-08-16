#ifndef LIFEBAR_HPP_INCLUDED
#define LIFEBAR_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class LifeBar : public sf::Drawable, sf::Transformable {
    private:
        static const int LIFEBAR_WIDTH = 400;
        static const int LIFEBAR_HEIGHT = 35;
        short int max;
        short int value;
        sf::RectangleShape background;
        sf::RectangleShape bar;
    public:
        LifeBar(short int max);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(this->background);
            target.draw(this->bar);
        }
        virtual void setPosition(float x, float y) {
            this->background.setPosition(x, y);
            this->bar.setPosition(x, y);
        }
        void increase(short int amount);
        void decrease(short int amount);
        void updateBar();
};

#endif
