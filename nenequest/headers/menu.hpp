#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "screen.hpp"

class Menu : public Screen {
   private:
    static const int TEXT_SIZE = 90;
    bool playing;

   public:
    Menu();
    virtual int run(sf::RenderWindow &app);
    short int validateMenu(short int menuIndex);
};

#endif
