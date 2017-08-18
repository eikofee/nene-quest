#ifndef GAMEOVER_HPP_INCLUDED
#define GAMEOVER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "gameover.hpp"

class GameOver : public Screen {
    private:
        sf::Color m_bgcolor = sf::Color(62, 64, 121);
    public:
        GameOver();
        virtual int run(sf::RenderWindow &app);
};

#endif
