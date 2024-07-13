#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

// TODO : Clean all this

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
#include "levelParser.hpp"
#include "lifebar.hpp"
#include "player.hpp"
#include "randomCloud.hpp"
#include "screen.hpp"
#include "screenState.hpp"
#include "weaponType.hpp"

class ConfigManager;
class ConfigParser;
class LevelManager;
class Game : public Screen {
   public:
    Game();
    virtual ScreenState run(sf::RenderWindow& app);
    virtual void clearAll();
    void addPlayerInstance(Player* player);
    void addInstance(Entity* e);
    static bool IsDebugMode();

   private:
    // void checkCollision(float elapsedTime, sf::Vector2u windowSize);
    // void scroll(float elapsedTime, sf::Vector2u windowSize);
    bool playerIsColliding(Player *p);
    // void playerMove(Player* player, float elapsedTime, sf::Vector2u
    // windowSize, float skyHeight);
    void drawWithDepth(sf::RenderWindow *app);
    static bool cmp(Entity *a, Entity *d);
    void manageInputs(sf::Event e, PlayerID id, sf::Keyboard::Key up,
                      sf::Keyboard::Key down, sf::Keyboard::Key left,
                      sf::Keyboard::Key right, sf::Keyboard::Key attack);

    // Final objetcs
    LevelManager *manager;
    LevelParser *parser;
    ConfigManager *configManager;
    ConfigParser *configParser;

    BreakableObject *getCollidingObject(Player *p);

    // std::vector<Enemy*> enemies

    std::vector<BonusHp *> bonuses_hp;
    std::vector<ItemWeapon *> item_weapons;
    std::vector<BreakableObject *> breakable_objects;
    BridgePit *bridge;

    static constexpr float SCROLL_SPEED = -0.1;
    static constexpr float PLAYER_SPEED = 0.5;
    static const int SCROLLING_DAMAGE = 10;

    LifeBar life;
    float player_invulnerability_timer = 0;

    static bool debugMode;
    void manageMetaInputs(sf::Event e, sf::Keyboard::Key toggleDebug);
};

#endif
