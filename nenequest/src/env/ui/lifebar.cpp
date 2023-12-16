#include "lifebar.hpp"
#include "player.hpp"

#include <iostream>

using namespace std;
using namespace sf;

LifeBar::LifeBar() {}

LifeBar::LifeBar(Vector2f position, PlayerID id) {

    this->background = RectangleShape(Vector2f(this->LIFEBAR_WIDTH, 35));
    this->background.setFillColor(Color::White);
    this->background.setOrigin(this->background.getSize().x / 2,
                               this->background.getSize().y / 2);
    this->background.setPosition(position);

    this->bar = RectangleShape(this->background.getSize());
    this->bar.setOrigin(this->bar.getSize().x / 2, this->bar.getSize().y / 2);
    this->bar.scale(0.99, 0.85);
    this->bar.setFillColor(Color::Green);
    this->bar.setPosition(position);

    switch (id) {
        case PlayerID::PLAYER1:
            this->knight_head_tex.loadFromFile("img/icon_p1.png");
            break;
        case PlayerID::PLAYER2:
            this->knight_head_tex.loadFromFile("img/icon_p2.png");
            break;
        default:
            break;
    }

    this->knight_head.setTexture(this->knight_head_tex);
    this->knight_head.setOrigin(this->background.getSize().x / 2 + 50,
                                this->background.getSize().y + 30);
    this->knight_head.setPosition(position);
}

void LifeBar::updateBar(int value) {
    float newLength =
        this->LIFEBAR_WIDTH * ((float) value / (float) (Player::PLAYER_MAX_HP));
    this->bar.setSize(Vector2f(newLength, this->LIFEBAR_HEIGHT));
}

void LifeBar::setValue(short int value) {
    if (value >= 0 && value <= (Player::PLAYER_MAX_HP)) updateBar(value);
}
