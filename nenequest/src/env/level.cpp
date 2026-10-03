#include "level.hpp"

#include <algorithm>
#include <iostream>

#include "boar.hpp"
#include "dragon.hpp"
#include "world.hpp"

using namespace std;
using namespace sf;

// Players can walk between y = 200 and y = 1080. Things spawn at the right
// edge when the camera reaches their distance, so with a 1920 px wide screen
// the dragon below ends up 1020 px from the left once the camera stops.
const vector<LevelEvent> level0 = {
    {0,    "scroll",  120},
    {0,    "chest",   430},
    {300,  "boar",    540},
    {700,  "onigiri", 900},
    {900,  "sword",   600},
    {1200, "boar",    400},
    {1300, "boar",    700},
    {1700, "barrel",  500},
    {1900, "barrel",  750},
    {2300, "boar",    450},
    {2500, "chest",   650},
    {2600, "onigiri", 850},
    {2800, "boar",    600},
    {2900, "boar",    350},
    {3100, "dragon",  400},
    {4000, "scroll",  0},  // The camera stops: boss arena
};

Level::Level(vector<LevelEvent> events) : events(std::move(events)) {
    // Stable, so events at the same distance fire in the written order
    stable_sort(this->events.begin(), this->events.end(),
                [](auto &a, auto &b) { return a.distance < b.distance; });
}

void Level::update() {
    float distance = World::getCameraBounds().left;
    while (next < events.size() && events[next].distance <= distance)
        fire(events[next++]);
}

void Level::fire(const LevelEvent &event) {
    FloatRect camera = World::getCameraBounds();
    Vector2f position(camera.left + camera.width, event.value);

    if (event.what == "scroll")
        World::setScrollSpeed(event.value);
    else if (event.what == "boar")
        World::addEntity(make_unique<Boar>(position));
    else if (event.what == "dragon")
        World::addEntity(make_unique<Dragon>(position));
    else if (event.what == "chest")
        World::addEntity(make_unique<BreakableObject>(Chest, position));
    else if (event.what == "barrel")
        World::addEntity(make_unique<BreakableObject>(Barrel, position));
    else if (event.what == "onigiri")
        World::addEntity(make_unique<BonusHp>(BONUS_ONIGIRI, position));
    else if (event.what == "axe")
        World::addEntity(make_unique<ItemWeapon>(Axe, position));
    else if (event.what == "sword")
        World::addEntity(make_unique<ItemWeapon>(Sword, position));
    else if (event.what == "greatsword")
        World::addEntity(make_unique<ItemWeapon>(GreatSword, position));
    else if (event.what == "bow")
        World::addEntity(make_unique<ItemWeapon>(Bow, position));
    else
        cerr << "Unknown level event: " << event.what << endl;
}
