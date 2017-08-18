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



class Game : public Screen {
    public:
        Game();
        virtual int run(sf::RenderWindow &app);

    private:
        void checkCollision();

        std::vector<Enemy*> enemies;
        std::vector<Player*> players;
        std::vector<BonusHp*> bonuses_hp;
        std::vector<ItemWeapon*> item_weapons;

        LifeBar life;

};

#endif
