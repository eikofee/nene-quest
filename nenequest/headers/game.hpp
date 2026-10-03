#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "arrow.hpp"
#include "background.hpp"
#include "boar.hpp"
#include "bonus.hpp"
#include "bonusHp.hpp"
#include "breakableObject.hpp"
#include "bridgePit.hpp"
#include "dragon.hpp"
#include "enemy.hpp"
#include "flame.hpp"
#include "itemWeapon.hpp"
#include "lifebar.hpp"
#include "player.hpp"
#include "randomCloud.hpp"
#include "screen.hpp"
#include "screenState.hpp"
#include "weaponType.hpp"

class Game : public Screen {
   public:
    Game(int playerCount);
    virtual ScreenState run(sf::RenderWindow& app);
    void clearAll();
    static bool IsDebugMode();

   private:

    int playerCount;
    void manageInputs(sf::Event e, PlayerID id, sf::Keyboard::Key up,
                      sf::Keyboard::Key down, sf::Keyboard::Key left,
                      sf::Keyboard::Key right, sf::Keyboard::Key attack);

    static bool debugMode;
    void manageMetaInputs(sf::Event e, sf::Keyboard::Key toggleDebug);
};

#endif
