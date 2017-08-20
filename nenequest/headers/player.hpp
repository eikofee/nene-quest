#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "../headers/movableentity.hpp"
#include "../headers/weapon.hpp"
#include "../headers/livingEntity.hpp"
#include "../headers/lifebar.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

static int PLAYER_HP = 10;

class Player : public MovableEntity
{
    public:
        Player(Weapon* weapon, sf::Vector2f(position));
        virtual ~Player();

        // Weapon
        Weapon* getWeapon();
        void attack();
        void equip(Weapon* w);

        // Life management
        LifeBar getLife();

        // override
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
        virtual void move(sf::Vector2f g_speed, float elapsedTime);

        // Jumping
        bool isJumping();
        void switchJump();

    private:
        bool is_attacking = false;
        bool animation_state = false;
        bool is_jumping = false;
        sf::Clock clock;
        static constexpr float ANIMATION_DELAY = 0.2;
        void update_animation();


        LifeBar life;
        sf::Vector2f speed = sf::Vector2f(-10,0);
        Weapon* weapon;
};

#endif // PLAYER_HPP_INCLUDED
