#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "game.hpp"
#include "gameover.hpp"
#include "menu.hpp"
#include "screen.hpp"
#include "screenState.hpp"

#define WINDOW_X 1920
#define WINDOW_Y 1080
#define WINDOW_NAME "Nene Quest"
#define FPS_RATE 60

int main() {
    std::map<ScreenState, Screen*> screens;
    ScreenState selectedScreen = TITLE_SCREEN;

    sf::RenderWindow app(sf::VideoMode(WINDOW_X, WINDOW_Y), WINDOW_NAME);
    app.setFramerateLimit(FPS_RATE);

    screens[TITLE_SCREEN] = new Menu();
    screens[GAME_SCREEN] = new Game();
    screens[GAME_OVER] = new GameOver();

    while (selectedScreen != EXIT_GAME)
        selectedScreen = screens[selectedScreen]->run(app);

    return EXIT_SUCCESS;
}
