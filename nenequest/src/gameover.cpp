#include <SFML/Audio.hpp>
#include "../headers/gameover.hpp"

using namespace std;
using namespace sf;

GameOver::GameOver() {
	std::string path = "img/gameover/";
	std::string ext = ".png";
	std::vector<std::string> texs = { "bg_u", "ba_u", "bm_u", "be_u", "o_u", "v_u", "e_u", "r_u", "!_u", "bg_o", "ba_o", "bm_o", "be_o", "o_o", "v_o", "e_o", "r_o", "!_o" };
	for (int i = 0; i < 18; i++) {
		Texture* letterTex = new Texture();
		letterTex->loadFromFile(path + texs.at(i) + ext);
		this->ww = letterTex->getSize().x;
		this->h = letterTex->getSize().y;
		Sprite* s = new Sprite(*letterTex);
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
				w->move(0, 10);
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

	for (int i = 0; i < 18; i++) {
		this->letters.at(i)->setPosition(app.getSize().x/2 - (1.4*this->ww) + (this->ww/((i % 9 > 3 ? 3.5 : 2.65))) * (i % 9) + (this->ww/ 2.65 * (i % 9 > 3 ? 2 : 0)), 0 - (i % 9) * h);

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
