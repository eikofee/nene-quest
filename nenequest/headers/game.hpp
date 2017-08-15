#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"

class Game : public Screen {
    public:
        Game();
        virtual int run(sf::RenderWindow &app);
};

#endif
