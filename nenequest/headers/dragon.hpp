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

    protected:

    private:
        std::vector<Flame*> flames;
        int movement_timer = 0;
        bool fire_breathing = false;
        void progressAnimation();
        short int flame_timer = 0;
};

#endif // DRAGON_H
