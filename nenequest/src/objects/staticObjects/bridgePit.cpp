#include "bridgePit.hpp"

using namespace sf;

BridgePit::BridgePit(float x, float groundHeight, unsigned int windowHeight) {
    texture.loadFromFile("img/background_bridge.png");
    sprite.setTexture(texture);

    float y = groundHeight - sprite.getLocalBounds().height;
    sprite.setPosition(x,
                       windowHeight - y / 2 - sprite.getLocalBounds().height);

    zHitboxes.push_back(
        new RectangleShape(Vector2f(sprite.getLocalBounds().width, y / 2)));
    zHitboxes.push_back(
        new RectangleShape(Vector2f(sprite.getLocalBounds().width, y / 2)));

    zHitboxes.at(0)->setPosition(x, windowHeight - groundHeight);
    zHitboxes.at(0)->setFillColor(Color::Black);

    zHitboxes.at(1)->setPosition(x, windowHeight - y / 2);
    zHitboxes.at(1)->setFillColor(Color::Black);

    ignoreDepthOnRendering = true;
}

BridgePit::~BridgePit() {
    // dtor
}

void BridgePit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto var : zHitboxes) target.draw(*var, states);
    target.draw(sprite, states);
}

FloatRect BridgePit::getSpriteBounds() { return sprite.getGlobalBounds(); }

EntityType BridgePit::getEntityType() { return SOLID; }
