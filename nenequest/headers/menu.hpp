#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "screenState.hpp"

class Menu : public Screen {
   public:
    Menu();
    ScreenState run(sf::RenderWindow &app) override;
    void clearAll() override;
   private:
    static const int TEXT_SIZE = 90;
};

#endif
