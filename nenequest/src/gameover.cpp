#include <SFML/Audio.hpp>
#include "../headers/gameover.hpp"
#include "../headers/gamemode.hpp"

using namespace std;
using namespace sf;

const string GameOver::GAMEOVER_PATH = "img/gameover/";
const string GameOver::GAMEOVER_EXT = ".png";

GameOver::GameOver(GameMode mode) {
	vector<string> texs = {
	    "bg_u", "ba_u", "bm_u", "be_u", "o_u", "v_u", "e_u", "r_u", "!_u",
	    "bg_o", "ba_o", "bm_o", "be_o", "o_o", "v_o", "e_o", "r_o", "!_o"
    };
	for (int i = 0; i < 18; i++) {
		Texture* letterTex = new Texture();
		letterTex->loadFromFile(this->GAMEOVER_PATH + texs.at(i) + this->GAMEOVER_EXT);
		this->ww = letterTex->getSize().x;
		this->h = letterTex->getSize().y;
		Sprite* s = new Sprite(*letterTex);
		s->setOrigin(letterTex->getSize().x/2, letterTex->getSize().y/2);
		this->letters.insert(this->letters.begin() + i, s);
	}
	this->mode = mode;
}

void GameOver::updateSprite(Vector2f origin) {
    Time elapsed = this->clockSprite.getElapsedTime();
    if (elapsed.asMilliseconds() >= 250) {
        for (auto s : this->playersDown)
            s->setPosition(origin);
        this->clockSprite.restart();
    }
    else if (elapsed.asMilliseconds() >= 125) {
        for (auto s : this->playersDown)
            s->setPosition(origin.x+1, origin.y+1);
    }
}

void GameOver::updateText() {
    Time elapsed = this->clockText.getElapsedTime();
    if(elapsed.asMilliseconds() >= 10) {
		for (auto w : this->letters) {
			//if (w->getPosition().y < this->textLimitY)
				//w->move(0, 10);
				w->move(0, fminf((this->textLimitY - w->getPosition().y) / 6, 30));
		}
		this->clockText.restart();
    }
}

void GameOver::freeGameOver() {
    // TODO : free letters
    for (auto p : this->playersDown)
        delete p;
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
		this->letters.at(i)->setPosition(
            app.getSize().x/2 - (1.3*this->ww) + (this->ww/((i % 9 > 3 ? 3.5 : 2.65))) * (i % 9) + (this->ww/ 1.7 * (i % 9 > 3 ? 1 : 0)),
            0 - (i % 9) * h *0.5
        );
	}
    this->textLimitY = (halo.getGlobalBounds().top)/2.0;

    Texture p1DownTex;
	p1DownTex.loadFromFile("img/gameover/p1_down.png");
    this->playersDown.push_back(new Sprite(p1DownTex));

    Texture p2DownTex;

    if (this->mode == TWO_PLAYER) {
        p2DownTex.loadFromFile("img/gameover/p2_down.png");
        this->playersDown.push_back(new Sprite(p2DownTex));

        this->playersDown[0]->setOrigin(0, p1DownTex.getSize().y/2);
        this->playersDown[0]->setPosition(halo.getPosition());
        this->playersDown[1]->setOrigin(p2DownTex.getSize().x, p2DownTex.getSize().y/2);
        this->playersDown[1]->setPosition(halo.getPosition());
    }
    else {
        this->playersDown[0]->setOrigin(p1DownTex.getSize().x/2, p1DownTex.getSize().y/2);
        this->playersDown[0]->setPosition(halo.getPosition());
    }

    SoundBuffer sfxBuffer;
    sfxBuffer.loadFromFile("sfx/gameover.ogg");
    Sound sfx(sfxBuffer);
    sfx.play();

    // ---------------- Main Loop ----------------
	while(running) {
		while(app.pollEvent(event)) {
			if (event.type == Event::Closed)
				return (-1);
			if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed) {
				this->freeGameOver();
				return 1;
			}
		}

		app.clear(this->m_bgcolor);
		app.draw(halo);
		this->updateSprite(halo.getPosition());
		for (auto p : this->playersDown)
            app.draw(*p);
		this->updateText();
		for (auto w : this->letters) app.draw(*w);
		app.display();
	}

	return (-1);
}
