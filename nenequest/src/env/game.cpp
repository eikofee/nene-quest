#include "game.hpp"

#include <stdlib.h>
#include <time.h>

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

    if (this->playerCount == 1) {
        World::setGameMode(ONE_PLAYER);
        Player *player = new Player(new Weapon(Axe), sf::Vector2f(50, 520));
        World::addPlayer(player);
    } else if (this->playerCount == 2) {
        World::setGameMode(TWO_PLAYERS);
        Player *player1 = new Player(new Weapon(Axe), sf::Vector2f(50, 520));
        World::addPlayer(player1);
        Player *player2 = new Player(new Weapon(Sword), sf::Vector2f(50, 560), true);
        World::addPlayer(player2);
    }

    // Test scene, until there is a level
    Boar *boar1 = new Boar(Vector2f(app.getSize().x - 1010, app.getSize().y / 2));
    World::addEntity(boar1);
    BonusHp *onigiri = new BonusHp(BONUS_ONIGIRI, Vector2f(900, 900));
    ItemWeapon *sword = new ItemWeapon(Sword, Vector2f(800, 600));
    World::addEntity(onigiri);
    World::addEntity(sword);
    BreakableObject *barrel = new BreakableObject(Chest, Vector2f(520, 430));
    World::addEntity(barrel);
    // Uncomment to test the boss:
    // World::addEntity(new Dragon(Vector2f(1000, 400)));

    Clock clock;
    // ---------------- Main Loop ----------------
    while (true) {

        float elapsedTime = clock.restart().asMilliseconds();

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
        World::updateEntities();
        World::updatePlayers();
        World::scroll();
        World::managePlayersCollidingWithThings();
        World::manageAttackingPlayers();

        background.update();
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
