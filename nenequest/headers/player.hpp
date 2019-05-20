#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

#include "weapon.hpp"
#include "lifebar.hpp"
#include "arrow.hpp"
#include "itemWeapon.hpp"
#include "entity.hpp"

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
        void isHit(int damage);
        virtual void alterHealth(int value, bool relative);

        // override
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
        void move(sf::Vector2f g_speed);
        virtual void setPosition(float x, float y);
        virtual EntityType getEntityType();

        // Jumping
        bool isJumping();
        void toggleJump();

        bool moving_up = false;
        bool moving_down = false;
        bool moving_left = false;
        bool moving_right = false;

        void setLastDroppedItem(ItemWeapon* item);
        ItemWeapon* getLastDroppedItem();
		bool isShooting();
		void setShootingState(bool state);

        static constexpr int PLAYER_HP = 100;

    private:
		static constexpr float PLAYER_SPEED = 500;
        static constexpr float INVULNERABILITY_DURATION = 1;

        bool is_attacking = false;
        bool animation_state = false;
		bool is_shooting = false;
		float attackTime = 0.1f;
		float currentAttackTime = 0;
		float currentInvulnerabilityTime = 0;

		// Weapon placement
		int weaponXOffset;
		int weaponYOffset;
		int weaponXOffsetVariation;
		int weaponYOffsetVariation;

        sf::Vector2f speed = sf::Vector2f(-10,0);
        std::vector<Arrow*> arrows;
        bool is_jumping = false;
        sf::Clock clock;
        static constexpr float ANIMATION_DELAY = 0.1;
        void update_animation();
		void manageMovements();
		sf::Vector2f fixMovements(sf::Vector2f movement);
		void fixPosition();



		void cleanArrows(float elapsedTime);
        ItemWeapon* last_dropped_item = NULL;

        LifeBar* life;
        Weapon* weapon;
};

#endif
