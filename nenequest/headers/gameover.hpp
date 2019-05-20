#ifndef GAMEOVER_HPP_INCLUDED
#define GAMEOVER_HPP_INCLUDED

#include <math.h>
#include <SFML/Graphics.hpp>

#include "screen.hpp"
#include "gamemode.hpp"

class GameOver : public Screen {
    private:
        GameMode mode;
        static const std::string GAMEOVER_PATH;
        static const std::string GAMEOVER_EXT;
        std::vector<sf::Sprite*> playersDown;
		std::vector<sf::Sprite*> letters;
        sf::Color m_bgcolor = sf::Color(62, 64, 121);
        sf::Clock clockSprite;
        sf::Clock clockText;
        float textLimitY;
        bool textFinished = false;
		sf::Vector2f lettersSize;
		std::vector<std::string> texs = {
			"bg_u", "ba_u", "bm_u", "be_u", "o_u", "v_u", "e_u", "r_u", "!_u",
			"bg_o", "ba_o", "bm_o", "be_o", "o_o", "v_o", "e_o", "r_o", "!_o"
		};
    public:
        GameOver(GameMode mode);
        virtual int run(sf::RenderWindow &app);
        void updateSprite(sf::Vector2f origin);
        void updateText();
        void freeGameOver();
};

#endif
