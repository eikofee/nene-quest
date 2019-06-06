#ifndef SCREENS_HPP_INCLUDED
#define SCREENS_HPP_INCLUDED

// Are those includes usefull ?
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "gameover.hpp"
#include "menu.hpp"
#include "screen.hpp"

enum ScreenEnum {
    TITLE_SCREEN = 0,
    GAME_SCREEN = 1,
    GAME_OVER_1P = 2,
    GAME_OVER_2P = 3
};

#endif
