#ifndef GAMEOVER_HPP_INCLUDED
#define GAMEOVER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "gameover.hpp"
#include <math.h>

class GameOver : public Screen {
    private:
        sf::Color m_bgcolor = sf::Color(62, 64, 121);
        sf::Clock clockSprite;
        sf::Clock clockText;
        float textLimitY;
        std::vector<sf::Sprite*> letters;
        bool textFinished = false;
		int ww;
		int h;
    public:
        GameOver();
        virtual int run(sf::RenderWindow &app);
        void updateSprite(sf::Sprite* s, sf::Vector2f origin);
        void updateText();
};

#endif
