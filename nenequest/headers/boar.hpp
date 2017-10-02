#ifndef BOAR_HPP
#define BOAR_HPP

#include "../headers/enemy.hpp"

#include <SFML/Graphics.hpp>

class Boar : public Enemy {

    public:
        Boar(sf::Vector2f position = sf::Vector2f(0,0));
        virtual ~Boar();
        void update(float elapsedTime);
        void stun();

    protected:

    private:
        static const int BOAR_DAMAGE = 1;
        static const int STUN_DURATION = 1000; //Milliseconds
        static constexpr float ANIMATION_DELAY = 0.1; //Seconds
        static constexpr float BOAR_SPEED = 10; //Pixels/millisecond

        bool is_stunned = false;
        int stun_timer = 0;
        void progressAnimation();

};

#endif // BOAR_HPP
