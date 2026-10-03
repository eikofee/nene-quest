#include "game.hpp"

#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>

#include "level.hpp"
#include "world.hpp"

using namespace std;
using namespace sf;

bool Game::debugMode;

Game::Game(int playerCount) {
    debugMode = true;
    this->playerCount = playerCount;
}

void Game::clearAll() {
    World::clearEntities();
    World::clearPlayers();
    World::clearLifebars();
}

ScreenState Game::run(RenderWindow& app) {

    Event event;
    Background background = Background(app.getSize());

    // Bind keys
    Keyboard::Key kbPlayerOneLeft = Keyboard::Left;
    Keyboard::Key kbPlayerOneRight = Keyboard::Right;
    Keyboard::Key kbPlayerOneUp = Keyboard::Up;
    Keyboard::Key kbPlayerOneDown = Keyboard::Down;
    Keyboard::Key kbPlayerOneAttack = Keyboard::Space;
    Keyboard::Key kbPlayerTwoLeft = Keyboard::Q;
    Keyboard::Key kbPlayerTwoRight = Keyboard::D;
    Keyboard::Key kbPlayerTwoUp = Keyboard::Z;
    Keyboard::Key kbPlayerTwoDown = Keyboard::S;
    Keyboard::Key kbPlayerTwoAttack = Keyboard::E;
    Keyboard::Key kbDebugMode = Keyboard::T;

    World::resetCamera(Vector2f(app.getSize()));

    if (this->playerCount == 1) {
        World::setGameMode(ONE_PLAYER);
        World::addPlayer(make_unique<Player>(make_unique<Weapon>(Axe),
                                             sf::Vector2f(50, 520)));
    } else if (this->playerCount == 2) {
        World::setGameMode(TWO_PLAYERS);
        World::addPlayer(make_unique<Player>(make_unique<Weapon>(Axe),
                                             sf::Vector2f(50, 520)));
        World::addPlayer(make_unique<Player>(make_unique<Weapon>(Sword),
                                             sf::Vector2f(50, 560), true));
    }

    Level level(level0);
    // To test the boss right away, use this level instead:
    // Level level({{0, "scroll", 900}, {0, "dragon", 400}, {900, "scroll", 0}});

    // Streamed from the file, and stopped when leaving this screen
    Music music;
    if (music.openFromFile("bgm/bgm.ogg")) {
        music.setLoop(true);
        music.play();
    }

    Clock clock;
    // ---------------- Main Loop ----------------
    while (true) {

        float elapsedTime = clock.restart().asSeconds();

        if (World::isVictory()) return this->gotoScreen(VICTORY);

        if(World::isGameOver()) {
            if (World::isTwoPlayer())
                return this->gotoScreen(GAME_OVER_2);
            return this->gotoScreen(GAME_OVER_1);
        }    

        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                return this->gotoScreen(EXIT_GAME);
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Escape){
                return this->gotoScreen(TITLE_SCREEN);
            }      
            
            manageInputs(event, PlayerID::PLAYER1, kbPlayerOneUp,
                            kbPlayerOneDown, kbPlayerOneLeft, kbPlayerOneRight,
                            kbPlayerOneAttack);

            if (World::isTwoPlayer())
                manageInputs(event, PlayerID::PLAYER2, kbPlayerTwoUp,
                            kbPlayerTwoDown, kbPlayerTwoLeft, kbPlayerTwoRight,
                            kbPlayerTwoAttack);

            manageMetaInputs(event, kbDebugMode);
        }

        World::setElapsedTime(elapsedTime);
        World::moveCamera();
        level.update();
        World::updateEntities();
        World::updatePlayers();
        World::crushPlayersAgainstSolids();
        World::managePlayersCollidingWithThings();
        World::managePlayersTouchingFlames();
        World::manageAttackingPlayers();

        background.setSpeed(World::getScrollSpeed());
        background.update(elapsedTime);
        app.clear(Color::White);
        app.draw(background);
        World::render(app);
        app.display();
    }

    return this->gotoScreen(EXIT_GAME);
}

// Temporary solution for input management
void Game::manageInputs(sf::Event e, PlayerID id, Keyboard::Key up,
                        Keyboard::Key down, Keyboard::Key left,
                        Keyboard::Key right, Keyboard::Key attack) {
    Player* player = World::getPlayer(id);
    if (!player) return;  // This player is dead
    if (e.type == Event::KeyPressed) {
        if (e.key.code == up)
            player->moving_up = true;
        else if (e.key.code == down)
            player->moving_down = true;
        else if (e.key.code == right)
            player->moving_right = true;
        else if (e.key.code == left)
            player->moving_left = true;
        else if (e.key.code == attack)
            player->attack();
    } else if (e.type == Event::KeyReleased) {
        if (e.key.code == up)
            player->moving_up = false;
        else if (e.key.code == down)
            player->moving_down = false;
        else if (e.key.code == right)
            player->moving_right = false;
        else if (e.key.code == left)
            player->moving_left = false;
        else if (e.key.code == attack)
            player->setShootingState(false);
    }
}

void Game::manageMetaInputs(sf::Event e, Keyboard::Key toggleDebug) {
    if (e.type == Event::KeyPressed) {
        if (e.key.code == toggleDebug) debugMode = !debugMode;
    }
}

bool Game::IsDebugMode() { return debugMode; }
