#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "../headers/weapon.hpp"
#include "../headers/lifebar.hpp"
#include "../headers/arrow.hpp"
#include"../headers/itemWeapon.hpp"
#include "../headers/entity.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

static int PLAYER_HP = 100;

class Player : public Entity {
    public:
        Player(Weapon* weapon, sf::Vector2f position, bool secondPlayer = false);
        ~Player();

        // Weapon
        Weapon* getWeapon();
        std::vector<Arrow*> getArrows();
        void attack();
        void fireArrow();
        void equip(Weapon* w);
        void update(float elapsedTime);

        // Life management
        LifeBar* getLife();

        // override
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
        virtual void move(sf::Vector2f g_speed, float elapsedTime);
        virtual void setPosition(float x, float y);

        // Jumping
        bool isJumping();
        void toggleJump();

        bool moving_up = false;
        bool moving_down = false;
        bool moving_left = false;
        bool moving_right = false;

        void setLastDroppedItem(ItemWeapon* item);
        ItemWeapon* getLastDroppedItem();

    private:
		static constexpr float PLAYER_SPEED = 0.5;
        bool is_attacking = false;
        bool animation_state = false;

        sf::Vector2f speed = sf::Vector2f(-10,0);
        std::vector<Arrow*> arrows;
        bool is_jumping = false;
        sf::Clock clock;
        static constexpr float ANIMATION_DELAY = 0.1;
        void update_animation();
		void manageMovements(float elapsedTime);
		sf::Vector2f fixMovements(sf::Vector2f movement);
		void fixPosition();

		void cleanArrows(float elapsedTime);
        ItemWeapon* last_dropped_item = NULL;

        LifeBar* life;
        Weapon* weapon;
};

#endif
