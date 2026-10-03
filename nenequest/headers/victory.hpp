#ifndef VICTORY_HPP_INCLUDED
#define VICTORY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "screen.hpp"
#include "screenState.hpp"

// Shown when the dragon is dead. Escape or Enter goes back to the title
class Victory : public Screen {
   public:
    ScreenState run(sf::RenderWindow &app) override;
    void clearAll() override;

   private:
    static const int TEXT_SIZE = 120;
    static constexpr float HOP_HEIGHT = 30.f;  // Pixels
    static constexpr float HOP_SPEED = 8.f;    // Radians/second
    sf::Color m_bgcolor = sf::Color(62, 64, 121);
};

#endif
