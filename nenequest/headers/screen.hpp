#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screenState.hpp"

class Screen {
  public:
    virtual ScreenState run(sf::RenderWindow &app) = 0;
    virtual void clearAll() = 0;
    ScreenState gotoScreen(ScreenState s) {
      clearAll(); return s;
    };
};

#endif
