#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "screenState.hpp"

class Menu : public Screen {
   public:
    Menu();
    ~Menu();
    virtual ScreenState run(sf::RenderWindow &app);
    bool isSelected(sf::Text*, int);
   private:
    static const int TEXT_SIZE = 90;
};

#endif
