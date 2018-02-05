#ifndef SCREENS_HPP_INCLUDED
#define SCREENS_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <screen.hpp>
#include <menu.hpp>
#include <game.hpp>
#include <gameover.hpp>

enum ScreenEnum {
	TITLE_SCREEN=0,
	GAME_SCREEN=1,
	GAME_OVER_1P=2,
	GAME_OVER_2P=3
};

#endif
