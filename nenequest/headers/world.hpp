#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "bonus.hpp"
#include "bonusHp.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "itemWeapon.hpp"
#include "player.hpp"
#include "gamemode.hpp"
#include "lifebar.hpp"
#include "breakableObject.hpp"

class World {
   public:
    static std::vector<Entity *> getEntities();
    static std::vector<Entity *> getCollidingEntities(Entity *entity);
    static std::vector<Entity *> getCollidingEntitiesOnZAxis(Entity *entity);
    // Added at the end of the next updateEntities(), so it's safe to call
    // while looping over the entities
    static void addEntity(std::unique_ptr<Entity> entity);
    static void addPlayer(std::unique_ptr<Player> player);
    static bool isTwoPlayer();
    static void setGameMode(GameMode gameMode);
    static bool isGameOver();
    static void clearEntities();
    static void clearPlayers();
    static void clearLifebars();
    static void updateEntities();
    static void updatePlayers();
    static void setElapsedTime(float time);  // Seconds
    static float getElapsedTime();
    static void render(sf::RenderWindow &app);
    static std::vector<Entity *> testCollidingEntitiesOnZAxis(
        Entity *entity, sf::Vector2f movement);
    static Player* getPlayer(PlayerID id);
    // The camera shows the part of the level on screen and moves right at
    // the scroll speed. Entities never move because of scrolling
    static void resetCamera(sf::Vector2f screenSize);
    static void moveCamera();
    static sf::FloatRect getCameraBounds();
    static void setScrollSpeed(float speed);  // Pixels/second
    static float getScrollSpeed();
    static void crushPlayersAgainstSolids();
    static void managePlayersCollidingWithThings();
    static void managePlayerCollidingWithBonus(Player *player, Bonus *bonus);
    static void managePlayerCollidingWithEnemy(Player *player, Enemy *enemy);
    // Management player's attacking 
    static void manageAttackingPlayers();
    static void manageWeaponCollidingWithThings(Player *player);

   private:
    // How far behind the camera an entity goes before it's removed
    static constexpr float FORGET_DISTANCE = 500.f;
    static constexpr float SCROLL_DAMAGE =
        30.f;  // When the player is pressed between the wall and a object by the
             // scrolling
    static GameMode gameMode;
    static std::vector<std::unique_ptr<Entity>> entities;
    static std::vector<std::unique_ptr<Entity>> spawned;  // Not added yet
    static std::vector<std::unique_ptr<Player>> players;
    static std::vector<std::unique_ptr<LifeBar>> lifebars;
    static float elapsedTime;
    static sf::View camera;
    static float scrollSpeed;
    static bool sortUsingFirstZHitbox(Entity *a, Entity *b);
};

#endif