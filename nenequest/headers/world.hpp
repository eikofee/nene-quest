#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <stdlib.h>
#include <SFML/Graphics.hpp>
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
    static void initialize();
    static void clearAll();
    static std::vector<Entity *> getEntities();
    static std::vector<Entity *> getNearEntities(sf::Vector2f position,
                                                 float radius);
    static std::vector<Entity *> getCollidingEntities(Entity *entity);
    static std::vector<Entity *> getCollidingEntitiesOnZAxis(Entity *entity);
    static void addEntity(Entity *entity);
    static void addPlayer(Player *player);
    static bool isTwoPlayer();
    static void setGameMode(GameMode gameMode);
    static bool isGameOver();
    static void clearEntities();
    static void clearPlayers();
    static void clearLifebars();
    static void updateEntities();
    static void updatePlayers();
    static void setElapsedTime(float time);
    static float getElapsedTime();
    static void render(sf::RenderWindow &app);
    static std::vector<Entity *> testCollidingEntities(Entity *entity,
                                                       sf::Vector2f movement);
    static std::vector<Entity *> testCollidingEntitiesOnZAxis(
        Entity *entity, sf::Vector2f movement);
    static std::vector<Player *> getPlayers();
    static Player* getPlayer(PlayerID id);
    static void scroll();
    static void managePlayersCollidingWithThings();
    static void managePlayerCollidingWithBonus(Player *player, Bonus *bonus);
    static void managePlayerCollidingWithEnemy(Player *player, Enemy *enemy);
    // Management player's attacking 
    static void manageAttackingPlayers();
    static void manageWeaponCollidingWithThings(Weapon *weapon);

   private:
    static constexpr float SCROLL_SPEED = 0.f; // Used to be 30
    static constexpr float SCROLL_DAMAGE =
        30.f;  // When the player is pressed between the wall and a object by the
             // scrolling
    static GameMode gameMode;
    static std::vector<Entity *> entities;
    static std::vector<Player *> players;
    static std::vector<LifeBar *> lifebars;
    static float elapsedTime;
    static bool sortUsingFirstZHitbox(Entity *a, Entity *b);
};

#endif