#include "game.hpp"

#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "world.hpp"

using namespace std;
using namespace sf;

bool Game::debugMode;

Game::Game(int playerCount) {
    // Final game objects (should only include Game, Players, LevelManagers and
    // other UI events)
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
    Keyboard::Key kbPlayerOneAttack = Keyboard::M;
    Keyboard::Key kbPlayerOneJump = Keyboard::L;
    Keyboard::Key kbPlayerTwoLeft = Keyboard::Q;
    Keyboard::Key kbPlayerTwoRight = Keyboard::D;
    Keyboard::Key kbPlayerTwoUp = Keyboard::Z;
    Keyboard::Key kbPlayerTwoDown = Keyboard::S;
    Keyboard::Key kbPlayerTwoAttack = Keyboard::E;
    Keyboard::Key kbPlayerTwoJump = Keyboard::Space;
    Keyboard::Key kbDebugMode = Keyboard::T;
    Keyboard::Key kbPause = Keyboard::Return;
     
    // Load Level
     // Testing objects////////////
   /* bridge = new BridgePit(300, app.getSize().y - background.getSkyHeight(),
                           app.getSize().y);
    World::addEntity(bridge); */
    if (this->playerCount == 1) {
        World::setGameMode(ONE_PLAYER);
        Player *player = new Player(new Weapon(Axe), sf::Vector2f(50, 520));
        World::addPlayer(player);
    } else if (this->playerCount == 2) {
        // don't remember if we did something for p1 and p2 to have different skins & weapons
        World::setGameMode(TWO_PLAYERS);
        Player *player1 = new Player(new Weapon(Axe), sf::Vector2f(50, 520));
        World::addPlayer(player1);
        Player *player2 = new Player(new Weapon(Sword), sf::Vector2f(50, 560), true);
        World::addPlayer(player2);
    }
    
    Boar *boar1 = new Boar(Vector2f(app.getSize().x - 1010, app.getSize().y / 2));
    World::addEntity(boar1);
    // Dragon *dragon = new Dragon(Vector2f(1000, 400));
    // World::addEntity(dragon);
    BonusHp *onigiri = new BonusHp(BONUS_ONIGIRI, Vector2f(900, 900));
    ItemWeapon *sword = new ItemWeapon(Sword, Vector2f(800, 600));
    World::addEntity(onigiri);
    World::addEntity(sword);
    // World::addEntity(new ItemWeapon(Axe, Vector2f(300, 630)));
    BreakableObject *barrel = new BreakableObject(Chest, Vector2f(520, 430)); 
    World::addEntity(barrel);
    // World::addEntity(new BreakableObject(Barrel, Vector2f(700, 430)));

    // // Arrow arrow = Arrow(Vector2f(100, 700), 700);
    // World::addEntity(new BreakableObject(Barrel, Vector2f(700, 430)));
    /////////////////////////////

    for (auto e : World::getEntities())
        cout << typeid(*e).name() << endl;

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
                            kbPlayerOneJump);

            if (World::isTwoPlayer())
                manageInputs(event, PlayerID::PLAYER2, kbPlayerTwoUp,
                            kbPlayerTwoDown, kbPlayerTwoLeft, kbPlayerTwoRight,
                            kbPlayerTwoJump);

            World::manageAttackingPlayers();

            manageMetaInputs(event, kbDebugMode);
        }

        World::setElapsedTime(elapsedTime);
        World::updateEntities();
        World::updatePlayers();
        World::scroll();
        World::managePlayersCollidingWithThings();

        // scroll(elapsedTime, app.getSize());

        background.update();
        // arrow.update(elapsedTime);
        // checkCollision(elapsedTime, app.getSize());
        app.clear(Color::White);
        app.draw(background);
        // app.draw(*bridge);
        World::render(app);
        // drawWithDepth(&app);
        // app.draw(arrow);
        app.display();
    }

    return this->gotoScreen(EXIT_GAME);
}

// Temporary solution for input management
void Game::manageInputs(sf::Event e, PlayerID id, Keyboard::Key up,
                        Keyboard::Key down, Keyboard::Key left,
                        Keyboard::Key right, Keyboard::Key attack) {
   // this->players = World::getPlayers(); // Moved before the main loop of the game
   // std::cout << "ManageInputs, size of players = " << this->players.size() << "\n";
   Player* player = World::getPlayer(id);
    if (e.type == Event::KeyPressed) {
        if (e.key.code == up)
            player->moving_up = true;
        else if (e.key.code == down)
            player->moving_down = true;
        else if (e.key.code == right)
            player->moving_right = true;
        else if (e.key.code == left)
            player->moving_left = true;
        else if (e.key.code == attack) {
            player->attack();
            /*if (!this->players.at(id)->isShooting())
                    this->players.at(id)->fireArrow();*/
        }
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

// Move to Render class
void Game::drawWithDepth(RenderWindow *app) {
    for (auto e : World::getEntities()) app->draw(*e);
}

bool Game::cmp(Entity *a, Entity *d) {
    if (a->getDrawDepth() >= d->getDrawDepth()) return false;
    return true;
}

bool Game::IsDebugMode() { return debugMode; }
