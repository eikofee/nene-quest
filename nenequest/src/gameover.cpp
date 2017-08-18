#include <SFML/Audio.hpp>
#include "../headers/gameover.hpp"

using namespace std;
using namespace sf;

GameOver::GameOver() {
    Texture* texteTex = new Texture();
    texteTex->loadFromFile("img/gameover/gameover_text.jpg");
    this->texte = new Sprite(*texteTex);
    this->texte->setOrigin(texteTex->getSize().x/2, texteTex->getSize().y/2);
}

void GameOver::updateSprite(Sprite* s, Vector2f origin) {
    Time elapsed = this->clockSprite.getElapsedTime();
    if (elapsed.asMilliseconds() >= 250) {
        s->setPosition(origin);
        this->clockSprite.restart();
    }
    else if (elapsed.asMilliseconds() >= 125)
        s->setPosition(origin.x+1, origin.y+1);
}

void GameOver::updateText() {
    Time elapsed = this->clockText.getElapsedTime();
    if (!this->textFinished && this->texte->getPosition().y >= this->textLimitY)
        this->textFinished = true;
    if (!this->textFinished && elapsed.asMilliseconds() >= 10) {
        this->texte->move(0, 5);
        this->clockText.restart();
    }
}

int GameOver::run(RenderWindow &app) {
	Event event;
	bool running = true;

	Texture haloTex;
	haloTex.loadFromFile("img/gameover/light.png");
    Sprite halo(haloTex);
    halo.setOrigin(haloTex.getSize().x/2, haloTex.getSize().y/2);
    halo.setPosition(app.getSize().x/2, app.getSize().y/2*1.25);

    this->texte->setPosition(app.getSize().x/2, 0);
    this->textLimitY = (halo.getGlobalBounds().top)/2.0;

    Texture p1DownTex;
	p1DownTex.loadFromFile("img/gameover/p1_down.png");
    Sprite* p1Down = new Sprite(p1DownTex);
    p1Down->setOrigin(p1DownTex.getSize().x/2, p1DownTex.getSize().y/2);
    p1Down->setPosition(halo.getPosition());

    SoundBuffer sfxBuffer;
    sfxBuffer.loadFromFile("sfx/gameover.ogg");
    Sound sfx(sfxBuffer);
    sfx.play();

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
		this->updateSprite(p1Down, halo.getPosition());
		app.draw(*p1Down);
		this->updateText();
		app.draw(*this->texte);
		app.display();
	}

	return (-1);
}
