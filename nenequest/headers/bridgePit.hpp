#ifndef BRIDGEPIT_H
#define BRIDGEPIT_H

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class BridgePit : public Entity
{
    public:
        BridgePit(float x, float groundHeight, unsigned int windowHeight);
        virtual ~BridgePit();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
        sf::FloatRect getSpriteBounds();
        virtual EntityType getEntityType();

    protected:

    private:
        sf::RectangleShape tmp;
};

#endif // BRIDGEPIT_H
