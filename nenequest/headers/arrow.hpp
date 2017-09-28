#ifndef ARROW_HPP
#define ARROW_HPP

#include "../headers/projectile.hpp"

class Arrow : public Projectile {
    public:
        static int const ARROW_DAMAGE = 1;
        Arrow(sf::Vector2f position, float g_depth);
        virtual ~Arrow();
        void update(float elapsedTime);
        bool isDead();
        void kill();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

    protected:

    private:
        bool is_dead = false;
        bool is_dying = false;
        float lifespan = 0;
        float gravity = 0.002;


        sf::Texture damage_texture;
        sf::Sprite damage_sprite;

        sf::Vector2f initial_location;
};

#endif // ARROW_HPP
