#ifndef BOAR_HPP
#define BOAR_HPP

#include "../headers/enemy.hpp"

#include <SFML/Graphics.hpp>

class Boar : public Enemy {

    public:
        Boar(sf::Vector2u windowSize, sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f g_speed = sf::Vector2f(-10,0));
        virtual ~Boar();
        void update(float elapsedTime);
        void stun();

    protected:

    private:
        bool is_stunned = false;
        sf::Vector2u window_size;
        int stun_timer = 0;
        void progressAnimation();

};

#endif // BOAR_HPP
