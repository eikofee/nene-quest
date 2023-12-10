#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screenState.hpp"

class Screen {
  public:
    virtual ScreenState run(sf::RenderWindow &app) = 0;
};

#endif
 