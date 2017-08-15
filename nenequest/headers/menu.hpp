#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"

class Menu : public Screen {
    private:
        bool playing;
    public:
        Menu();
        virtual int run(sf::RenderWindow &app);
};

#endif
