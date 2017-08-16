#include "../headers/game.hpp"
#include "../headers/lifebar.hpp"
#include "../headers/randomCloud.hpp"
#include "../headers/background.hpp"
#include "../headers/enemy.hpp"
#include "../headers/boar.hpp"

using namespace std;
using namespace sf;

Game::Game() {

}

int Game::run(RenderWindow &app) {
	Event event;
	bool running = true;

	// LifeBar
    LifeBar life(100);
	life.setPosition(300, 100);

	// Background
    Background background = Background(app.getSize());

	//Test cloud
	RandomCloud cloud;
	cloud.setPosition(500, 500);
	cloud.generateBorder();

	Boar boar1 = Boar(app.getSize(), Vector2f(app.getSize().x, app.getSize().y/2), Vector2f(-1,0));

    // ---------------- Main Loop ----------------
	while(running) {
		while(app.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return (-1);
			}
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
                    case Keyboard::Up:
                        boar1.stun();
                        break;
                    case Keyboard::Down:
                        break;
                    default:
                        break;
				}
			}
		}
		boar1.move();

		app.clear(Color::White);
        app.draw(background);
		app.draw(boar1);
		app.draw(life);
		app.draw(cloud);
		app.display();
	}

	return (-1);
}
