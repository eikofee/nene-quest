#include <SFML/Graphics.hpp>
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
    ScreenState selectedScreen = TITLE_SCREEN;

    sf::RenderWindow app(sf::VideoMode(WINDOW_X, WINDOW_Y), WINDOW_NAME);
    app.setFramerateLimit(FPS_RATE);

    while (selectedScreen != EXIT_GAME) {
        switch (selectedScreen) {
            case GAME_SCREEN_1:
                selectedScreen = (new Game(1))->run(app);
                break;
            
            case GAME_SCREEN_2:
                selectedScreen = (new Game(2))->run(app);
                break;

            case GAME_OVER_1:
                selectedScreen = (new GameOver())->run(app);
                break;
            
            case GAME_OVER_2:
                selectedScreen = (new GameOver())->run(app);
                break;

            default:
            case TITLE_SCREEN:
                selectedScreen = (new Menu())->run(app);
                break;
        }
    }

    return EXIT_SUCCESS;
}
