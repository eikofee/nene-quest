#include <SFML/Audio.hpp>
#include "../headers/gameover.hpp"

using namespace std;
using namespace sf;

GameOver::GameOver() {
	Texture* letterTex = new Texture();
	letterTex->loadFromFile("img/gameover/gameover_text.jpg");
	this->ww = letterTex->getSize().x / 9;
	this->h = letterTex->getSize().y;
	for (int i = 0; i < 8; i++) {
		Sprite* s = new Sprite(*letterTex);
		s->setTextureRect(IntRect(ww * i, 0, ww, h));
		s->setOrigin(letterTex->getSize().x/2, letterTex->getSize().y/2);
		this->letters.insert(this->letters.begin() + i, s);

	}
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
    if(elapsed.asMilliseconds() >= 10) {
		for (auto w : this->letters) {
			if (w->getPosition().y < this->textLimitY)
				w->move(0, 5);
		}

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

	for (int i = 0; i < 8; i++) {
		this->letters.at(i)->setPosition(app.getSize().x/2 + this->ww * i, 0 - i * h);

	}
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
		for (auto w : this->letters)
			app.draw(*w);

		app.display();
	}

	return (-1);
}
