#include "../headers/background.hpp"

using namespace sf;

Background::Background(Vector2u v) {
    int x = v.x;
    int y = v.y;

    this->sky = RectangleShape(Vector2f(x, y/3));
    this->sky.setFillColor(Color(115, 195, 226));

    this->ground = RectangleShape(Vector2f(x, y - this->sky.getSize().y));
    this->ground.setFillColor(Color(189, 132, 100));
    this->ground.setPosition(0, this->sky.getSize().y);
}

