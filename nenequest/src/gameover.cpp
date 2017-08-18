#include "../headers/gameover.hpp"

using namespace std;
using namespace sf;

GameOver::GameOver() {

}

int GameOver::run(RenderWindow &app) {
	Event event;
	bool running = true;

	Texture haloTex;
	haloTex.loadFromFile("img/gameover/light.png");
    Sprite halo(haloTex);
    halo.setOrigin(haloTex.getSize().x/2, haloTex.getSize().y/2);
    halo.setPosition(app.getSize().x/2, app.getSize().y/2*1.25);

    Texture p1DownTex;
	p1DownTex.loadFromFile("img/gameover/p1_down.png");
    Sprite p1Down(p1DownTex);
    p1Down.setOrigin(p1DownTex.getSize().x/2, p1DownTex.getSize().y/2);
    p1Down.setPosition(halo.getPosition());

    // ---------------- Main Loop ----------------
	while(running) {

		while(app.pollEvent(event)) {
			if (event.type == Event::Closed)
				return (-1);

            // Keyboard handling
			if (event.type == Event::KeyPressed)
				return 1;
            // Mouse handling
            if (event.type == Event::MouseButtonPressed)
                return 1;
		}

		app.clear(this->m_bgcolor);
		app.draw(halo);
		app.draw(p1Down);
		app.display();
	}

	return (-1);
}
