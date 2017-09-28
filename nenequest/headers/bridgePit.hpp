#ifndef BRIDGEPIT_H
#define BRIDGEPIT_H

#include <SFML/Graphics.hpp>
#include "../headers/movableEntity.hpp"

class BridgePit : public Entity
{
    public:
        BridgePit(float x, float groundHeight, unsigned int windowHeight);
        virtual ~BridgePit();
        virtual bool detectHit(Entity* entity);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
        sf::FloatRect getSpriteBounds();

    protected:

    private:
        std::vector<sf::RectangleShape> hitboxes;
        sf::RectangleShape tmp;
};

#endif // BRIDGEPIT_H
