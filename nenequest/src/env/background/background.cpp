#include "background.hpp"

#include <algorithm>

#include "randomCloud.hpp"
#include "randomMountain.hpp"

using namespace sf;

// TODO : Move the createClouds and createMountains in another class ?

Background::Background(Vector2u v) {
    // Cloud stuff
    this->v = v;
    srand(time(NULL));

    int x = v.x;
    int y = v.y;

    this->sky = RectangleShape(Vector2f(x, y / 2.5f));
    this->sky.setFillColor(Color(115, 195, 226));

    this->ground = RectangleShape(Vector2f(x, y - this->sky.getSize().y));
    this->ground.setFillColor(Color(189, 132, 100));
    this->ground.setPosition(0, this->sky.getSize().y);
}

void Background::update(float elapsedTime) {
    auto del = [](RandomShape *r) {
        bool b = !r->isAlive();
        if (b) delete r;
        return b;
    };
    auto upd = [&del, elapsedTime, this](std::vector<RandomShape *> &shapes,
                            float speedModifier) {
        auto rm = std::remove_if(shapes.begin(), shapes.end(), del);
        for (auto it = shapes.begin(); it != rm; ++it) {
            (*it)->translate(
                -(scrollSpeed + DRIFT_SPEED) * speedModifier * elapsedTime, 0);
            (*it)->update();
        }
        shapes.erase(rm, shapes.end());
    };
    upd(this->clouds, this->cloudSpeedModifier);
    upd(this->mountains, this->mountainSpeedModifier);

    this->cloudDistance += scrollSpeed * elapsedTime;
    this->mountainDistance += scrollSpeed * elapsedTime;
    this->createClouds();
    this->createMountains();
}

void Background::createClouds() {
    if (this->cloudDistance >= this->nextCloud) {
        RandomCloud *nc = new RandomCloud();
        nc->setPosition(
            v.x + 250 /*cloud width*/,
            rand() % this->CLOUD_SPAWN_Y_BOTTOM + this->CLOUD_SPAWN_Y_TOP);
        nc->generateBorder();
        this->clouds.insert(clouds.begin(), nc);

        this->nextCloud = rand() % (this->CLOUD_SPAWN_INTERVAL_RANDOM * 2) -
                          this->CLOUD_SPAWN_INTERVAL_RANDOM +
                          this->CLOUD_SPAWN_INTERVAL;
        this->cloudDistance = 0;
    }
}

void Background::createMountains() {
    if (this->mountainDistance >= this->nextMountain) {
        RandomMountain *nm = new RandomMountain();
        nm->setPosition(v.x + 250 /*cloud width*/,
                        this->sky.getSize().y + MOUNTAIN_VAR_Y_OFFSET);
        this->mountains.insert(mountains.begin(), nm);

        this->nextMountain =
            rand() % (this->MOUNTAIN_SPAWN_INTERVAL_RANDOM * 2) -
            this->MOUNTAIN_SPAWN_INTERVAL_RANDOM +
            this->MOUNTAIN_SPAWN_INTERVAL;
        this->mountainDistance = 0;
    }
}

void Background::setSpeed(float speed) { this->scrollSpeed = speed; }

float Background::getSkyHeight() { return this->sky.getLocalBounds().height; }
