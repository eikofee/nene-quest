#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "../headers/lifebar.hpp"
#include "../headers/randomCloud.hpp"
#include "../headers/background.hpp"
#include "../headers/enemy.hpp"
#include "../headers/boar.hpp"
#include "../headers/dragon.hpp"
#include "../headers/player.hpp"
#include "../headers/bonusHp.hpp"
#include "../headers/itemWeapon.hpp"
#include "../headers/flame.hpp"
#include "../headers/weaponType.hpp"
#include "../headers/breakableObject.hpp"
#include "../headers/bonus.hpp"


class Game : public Screen {
    public:
        Game();
        virtual int run(sf::RenderWindow &app);


    private:
        void checkCollision(float elapsedTime, sf::Vector2u windowSize);
        void scroll(float elapsedTime);
        bool playerIsColliding(Player* p);
        BreakableObject* getCollidingObject(Player* p);

        std::vector<Enemy*> enemies;
        std::vector<Player*> players;
        std::vector<BonusHp*> bonuses_hp;
        std::vector<ItemWeapon*> item_weapons;
        std::vector<BreakableObject*> breakable_objects;


        static constexpr float SCROLL_SPEED = -0.1;
        static constexpr float PLAYER_SPEED = 0.5;
        static const int SCROLLING_DAMAGE = 10;

        LifeBar life;
        float player_invulnerability_timer = 0;

};

#endif
