#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Screen {
  public:
   virtual int run(sf::RenderWindow &app) = 0;
   virtual void cleanScreen() = 0;
};

#endif
