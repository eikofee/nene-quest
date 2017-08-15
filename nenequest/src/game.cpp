#include "../headers/game.hpp"

using namespace std;
using namespace sf;

Game::Game() {

}

int Game::run(RenderWindow &app) {
	Event event;
	bool running = true;

    // ---------------- Main Loop ----------------
	while(running) {
		while(app.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return (-1);
			}
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
                    case Keyboard::Up:
                        break;
                    case Keyboard::Down:
                        break;
                    default:
                        break;
				}
			}
		}

		app.clear(Color::Black);
		app.display();
	}

	return (-1);
}
