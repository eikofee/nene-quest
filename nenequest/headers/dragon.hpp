#ifndef DRAGON_H
#define DRAGON_H

#include <SFML/Graphics.hpp>
#include <enemy.hpp>
#include <flame.hpp>


class Dragon : public Enemy {

    public:
        Dragon(sf::Vector2f position = sf::Vector2f(0,0));
        ~Dragon();
        void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const; //???
		void update(float elapsedTime);
		void breathFire();
        bool isBreatingFire();
        std::vector<Flame*> getFlames();	//Should be projectile ?
        //void setPosition(int x, int y);
        //void move(float elapsedTime);
		//void move(sf::Vector2f g_speed, float elapsedTime);
        //bool detectHit(Entity* entity);

    protected:

    private:
        static int const DRAGON_DAMAGE = 2;
        static int const MOVEMENT_DURATION = 1000; //Milliseconds
        static int const DELAY_BETWEEN_FLAMES = 100; //Milliseconds
        static float constexpr ANIMATION_DELAY = 0.5;//Seconds
        static float constexpr DRAGON_SPEED = 0.1;//Pixels/milliseconds
        static float constexpr DEAD_ANIMATION_DURATION = 6000;//Milliseconds

        std::vector<Flame*> flames;
        std::vector<sf::RectangleShape> hitboxes;
		sf::Vector2f computeMove(float elapsedTime);


        float movement_timer = 0;
        bool fire_breathing = false;
        void progressAnimation();
        float flame_timer = 0;
        float dying_timer = 0;
};

#endif // DRAGON_H
