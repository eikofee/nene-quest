#ifndef ARROW_HPP
#define ARROW_HPP

#include "../headers/movableEntity.hpp"


class Arrow : public MovableEntity
{
    public:
        Arrow(sf::Vector2f position);
        virtual ~Arrow();
        void update(float elapsedTime);
        bool isDead();
        void kill();

    protected:

    private:
        bool is_dead = false;
        float lifespan = 0;
        sf::Vector2f initial_location;
};

#endif // ARROW_HPP
