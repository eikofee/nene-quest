#ifndef BRIDGEPIT_H
#define BRIDGEPIT_H

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class BridgePit : public Entity {
   public:
    BridgePit(float x, float groundHeight, unsigned int windowHeight);
    virtual ~BridgePit();
    void draw(
        sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates::Default) const override;
    EntityType getEntityType() override;

   protected:
   private:
    sf::RectangleShape tmp;
};

#endif  // BRIDGEPIT_H
