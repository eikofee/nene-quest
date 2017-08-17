#ifndef DRAGON_H
#define DRAGON_H

#include <SFML/Graphics.hpp>
#include "../headers/enemy.hpp"


class Dragon : public Enemy {

    public:
        Dragon(sf::Vector2f position = sf::Vector2f(0,0));
        virtual ~Dragon();
        void update(float elapsedTime);

    protected:

    private:
        int movement_timer = 0;
};

#endif // DRAGON_H
