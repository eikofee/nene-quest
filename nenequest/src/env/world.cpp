#include "world.hpp"
#include <string.h>

#include <algorithm>

#include "flame.hpp"

using namespace std;

GameMode World::gameMode;
bool World::dragonDefeated = false;
std::vector<std::unique_ptr<Entity>> World::entities;
std::vector<std::unique_ptr<Entity>> World::spawned;
std::vector<std::unique_ptr<Player>> World::players;
std::vector<std::unique_ptr<LifeBar>> World::lifebars;

float World::elapsedTime;
sf::View World::camera;
float World::scrollSpeed = 0.f;

std::vector<Entity *> World::getEntities() {
    std::vector<Entity *> result;
    for (auto &e : entities) result.push_back(e.get());
    return result;
}

// Unused for now, but projectiles (arrows, flames) will need it to hit things
std::vector<Entity *> World::getCollidingEntities(Entity *entity) {
    std::vector<Entity *> result;
    for (auto &e : entities)
        if (e.get() != entity && !e->isDead()) {
            bool collide = false;
            for (auto h : e->getHitboxes())
                for (auto sh : entity->getHitboxes())
                    if (h->getGlobalBounds().intersects(
                            sh->getGlobalBounds()) &&
                        !collide) {
                        result.push_back(e.get());
                        collide = true;
                    }
        }

    return result;
}

std::vector<Entity *> World::getCollidingEntitiesOnZAxis(Entity *entity) {
    std::vector<Entity *> result;
    for (auto &e : entities)
        if (e.get() != entity && !e->isDead()) {
            bool collide = false;
            for (auto h : e->getZHitboxes())
                for (auto sh : entity->getZHitboxes())
                    if (h->getGlobalBounds().intersects(
                            sh->getGlobalBounds()) &&
                        !collide) {
                        result.push_back(e.get());
                        collide = true;
                    }
        }

    return result;
}

std::vector<Entity *> World::testCollidingEntitiesOnZAxis(
    Entity *entity, sf::Vector2f movement) {
    std::vector<Entity *> result;
    for (auto sh : entity->getZHitboxes()) {
        sf::RectangleShape testHitbox = sf::RectangleShape(*sh);
        testHitbox.move(movement);
        for (auto &e : entities)
            if (e.get() != entity && !e->isDead()) {
                bool collide = false;
                for (auto h : e->getZHitboxes())
                    if (h->getGlobalBounds().intersects(
                            testHitbox.getGlobalBounds()) &&
                        !collide) {
                        result.push_back(e.get());
                        collide = true;
                    }
            }
    }

    return result;
}

void World::setElapsedTime(float time) { elapsedTime = time; }

void World::addEntity(std::unique_ptr<Entity> entity) {
    spawned.push_back(std::move(entity));
}

void World::addPlayer(std::unique_ptr<Player> player) {
    players.push_back(std::move(player));
    if (players.size() == 1)
        lifebars.push_back(
            make_unique<LifeBar>(Vector2f(300, 100), PlayerID::PLAYER1));
    else
        lifebars.push_back(
            make_unique<LifeBar>(Vector2f(800, 100), PlayerID::PLAYER2));
}

void World::clearEntities() {
    entities.clear();
    spawned.clear();
    dragonDefeated = false;
}

void World::clearPlayers() {
    players.clear();
}

void World::clearLifebars() {
    lifebars.clear();
}

void World::updateEntities() {
    float forgetX = getCameraBounds().left - FORGET_DISTANCE;
    for (auto &e : entities) {
        e->update(elapsedTime);
        sf::FloatRect bounds = e->getZHitboxes().at(0)->getGlobalBounds();
        if (bounds.left + bounds.width < forgetX) {
            e->markDead();  // Far behind the camera, it won't be seen again
            continue;       // So a chest left behind drops nothing
        }
        if (e->isDead()) {
            if (dynamic_cast<Dragon *>(e.get())) dragonDefeated = true;
            // Barrels may drop nothing, and other SOLID entities never drop
            auto object = dynamic_cast<BreakableObject *>(e.get());
            if (object) {
                std::unique_ptr<Bonus> drop = object->getDrops();
                if (drop) addEntity(std::move(drop));
            }
        }
    }
    entities.erase(remove_if(entities.begin(), entities.end(),
                             [](auto &e) { return e->isDead(); }),
                   entities.end());

    // Only now, so nothing is added to entities while looping over it
    for (auto &e : spawned) entities.push_back(std::move(e));
    spawned.clear();
}

bool World::isTwoPlayer() {
    return gameMode == TWO_PLAYERS;
}

void World::setGameMode(GameMode x) {
    gameMode = x;
}


bool World::isVictory() { return dragonDefeated; }

bool World::isGameOver() {
    return (players.size() == 0);
}

void World::updatePlayers() {
    for (auto &p : players) p->update(elapsedTime);
    players.erase(remove_if(players.begin(), players.end(),
                            [](auto &p) { return p->isDead(); }),
                  players.end());
}

float World::getElapsedTime() { return elapsedTime; }

void World::render(sf::RenderWindow &app) {
    auto byDepth = [](auto &a, auto &b) {
        return sortUsingFirstZHitbox(a.get(), b.get());
    };
    std::sort(entities.begin(), entities.end(), byDepth);
    std::sort(players.begin(), players.end(), byDepth);

    app.setView(camera);
    for (auto &e : entities) app.draw(*e);
    for (auto &e : players) app.draw(*e);
    // The lifebars stay in place on the screen
    app.setView(app.getDefaultView());
    for (auto &e : lifebars) { app.draw(*e); }
}

Player* World::getPlayer(PlayerID id) {
    for (auto &p : players) {
        if (p->getId() == id) {
            return p.get();
        }
    }

    return NULL;
}


bool World::sortUsingFirstZHitbox(Entity *a, Entity *b) {
    if (a->isIgnoringDepthOnRendering()) return true;
    if (b->isIgnoringDepthOnRendering()) return false;

    auto ha = a->getZHitboxes().at(0)->getPosition().y +
              a->getZHitboxes().at(0)->getSize().y;
    auto hb = b->getZHitboxes().at(0)->getPosition().y +
              b->getZHitboxes().at(0)->getSize().y;
    return ha < hb;
}

void World::managePlayersCollidingWithThings() {
    for (auto &player : players)
        for (Entity *ent : World::getCollidingEntitiesOnZAxis(player.get())) {
            switch (ent->getEntityType()) {
                case EntityType::BONUS:
                    World::managePlayerCollidingWithBonus(player.get(),
                                                          (Bonus *)ent);
                    break;
                case EntityType::ENEMY:
                    World::managePlayerCollidingWithEnemy(player.get(),
                                                          (Enemy *)ent);
                    break;
                case EntityType::NONE:
                case EntityType::PLAYER:
                case EntityType::SFX:
                case EntityType::SOLID:
                    break;  // do nothing?
            }
        }
}

void World::managePlayerCollidingWithBonus(Player *player, Bonus *bonus) {
    switch (bonus->getBonusType()) {
        case BONUS_HP:
            { short valueHealed = ((BonusHp *)bonus)->getHealedAmount();
            player->alterHealth(valueHealed, true);
            lifebars.at(player->getId())->updateBar(player->getHealth());
            bonus->markDead();
            break;
            }
        case BONUS_WEAPON:
            if (((ItemWeapon *)bonus)->isPickable()) {
                WeaponType playerWeapon = player->getWeapon()->getWeaponType();
                player->equip(make_unique<Weapon>(
                    ((ItemWeapon *)bonus)->getWeaponType()));
                ((ItemWeapon *)bonus)->setWeaponType(playerWeapon);
                ((ItemWeapon *)bonus)->isJustDropped();
            }
            break;
    }
}

void World::manageAttackingPlayers() {
    for (auto &player : players) {
        if (player->isAttacking())
            manageWeaponCollidingWithThings(player.get());
    }
}

void World::manageWeaponCollidingWithThings(Player *player) {
    Weapon *weapon = player->getWeapon();
    vector<Entity *> collided = getCollidingEntitiesOnZAxis(weapon);
    for(auto e : collided) {
        // Checked every frame, but an attack hits each thing only once
        if (!player->hitOnce(e)) continue;
        switch (e->getEntityType()) {
            case ENEMY:
                e->alterHealth(- weapon->getDamage(), true);
                ((Enemy *)e)->stun();
                break;
            case NONE:
            case PLAYER:
            case SFX:
            case SOLID:
                e->alterHealth(- weapon->getDamage(), true);
            case BONUS:
                break;  // do nothing?
        }
    }

}

void World::managePlayerCollidingWithEnemy(Player *player, Enemy *enemy) {
    if (enemy->isDying()) return;  // Harmless during its death animation
    short ennemyDamage = enemy->getAttackDamage();
    player->isHit(ennemyDamage);
    lifebars.at(player->getId())->updateBar(player->getHealth());
}

void World::resetCamera(sf::Vector2f screenSize) {
    camera = sf::View(sf::FloatRect(0, 0, screenSize.x, screenSize.y));
    scrollSpeed = 0.f;
}

void World::moveCamera() { camera.move(scrollSpeed * elapsedTime, 0); }

sf::FloatRect World::getCameraBounds() {
    sf::Vector2f size = camera.getSize();
    return sf::FloatRect(camera.getCenter() - size / 2.f, size);
}

void World::setScrollSpeed(float speed) { scrollSpeed = speed; }

float World::getScrollSpeed() { return scrollSpeed; }

// The camera pushes players forward, and players can't walk into solids, so
// a player overlapping a solid has been pressed against it by the camera
void World::crushPlayersAgainstSolids() {
    for (auto &player : players)
        for (Entity *e : getCollidingEntitiesOnZAxis(player.get()))
            if (e->getEntityType() == SOLID) {
                e->markDead();
                player->isHit(SCROLL_DAMAGE);
                lifebars.at(player->getId())->updateBar(player->getHealth());
            }
}

// The dragon owns its flames, so they aren't in the entities
void World::managePlayersTouchingFlames() {
    for (auto &e : entities) {
        auto dragon = dynamic_cast<Dragon *>(e.get());
        // The dying dragon's flames are only for show
        if (!dragon || dragon->isDying()) continue;
        for (Projectile *flame : dragon->getFlames())
            for (auto &player : players)
                if (flame->getHitboxes().at(0)->getGlobalBounds().intersects(
                        player->getHitboxes().at(0)->getGlobalBounds())) {
                    player->isHit(Flame::FLAMES_DAMAGE);
                    lifebars.at(player->getId())
                        ->updateBar(player->getHealth());
                }
    }
}
