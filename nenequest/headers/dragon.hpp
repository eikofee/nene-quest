#ifndef DRAGON_H
#define DRAGON_H

#include <SFML/Graphics.hpp>
#include "../headers/enemy.hpp"
#include "../headers/flame.hpp"


class Dragon : public Enemy {

    public:
        Dragon(int hp, sf::Vector2f position = sf::Vector2f(0,0));
        virtual ~Dragon();
        virtual void update(float elapsedTime);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
        void breathFire();
        bool isBreatingFire();
        std::vector<Flame*> getFlames();
        virtual void setPosition(int x, int y);
        virtual void move(float elapsedTime);
		virtual void move(sf::Vector2f g_speed, float elapsedTime);
        virtual bool detectHit(Entity* entity);
        virtual float getDepth();

    protected:

    private:
        static int const DRAGON_DAMAGE = 2;
        static int const MOVEMENT_DURATION = 1000; //Milliseconds
        static int const DELAY_BETWEEN_FLAMES = 100; //Milliseconds
        static float constexpr ANIMATION_DELAY = 0.5;//Seconds
        static float constexpr DRAGON_SPEED = 0.1;//Pixels/milliseconds

        std::vector<Flame*> flames;
        std::vector<sf::RectangleShape> hitboxes;


        int movement_timer = 0;
        bool fire_breathing = false;
        void progressAnimation();
        short int flame_timer = 0;
};

#endif // DRAGON_H
