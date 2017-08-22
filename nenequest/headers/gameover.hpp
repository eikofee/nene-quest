#ifndef GAMEOVER_HPP_INCLUDED
#define GAMEOVER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "gameover.hpp"
#include "gamemode.hpp"
#include <math.h>

class GameOver : public Screen {
    private:
        GameMode mode;
        static const std::string GAMEOVER_PATH;
        static const std::string GAMEOVER_EXT;
        std::vector<sf::Sprite*> playersDown;
        sf::Color m_bgcolor = sf::Color(62, 64, 121);
        sf::Clock clockSprite;
        sf::Clock clockText;
        float textLimitY;
        std::vector<sf::Sprite*> letters;
        bool textFinished = false;
		int ww;
		int h;
    public:
        GameOver(GameMode mode);
        virtual int run(sf::RenderWindow &app);
        void updateSprite(sf::Vector2f origin);
        void updateText();
        void freeGameOver();
};

#endif
