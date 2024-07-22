#include <SFML/Audio.hpp>
#include "gameover.hpp"
#include "gamemode.hpp"

using namespace std;
using namespace sf;

const string GameOver::GAMEOVER_PATH = "img/gameover/";
const string GameOver::GAMEOVER_EXT = ".png";

GameOver::GameOver() { }

void GameOver::updateSprite(Vector2f origin) {
    Time elapsed = this->clockSprite.getElapsedTime();
    if (elapsed.asMilliseconds() >= 250) {
        for (auto s : this->playersDown) s->setPosition(origin);
        this->clockSprite.restart();
    } else if (elapsed.asMilliseconds() >= 125) {
        for (auto s : this->playersDown)
            s->setPosition(origin.x + 1, origin.y + 1);
    }
}

void GameOver::updateText() {
    Time elapsed = this->clockText.getElapsedTime();
    if (elapsed.asMilliseconds() >= 10) {
        for (auto w : this->letters) {
            w->move(0, fminf((this->textLimitY - w->getPosition().y) / 6, 30));
        }
        this->clockText.restart();
    }
}

void GameOver::clearAll() {
    for (auto l : this->letters) delete l;
    for (auto p : this->playersDown) delete p;
    this->letters.clear();
    this->playersDown.clear();
}

ScreenState GameOver::run(RenderWindow &app) {
    Event event;

    // Place Halo
    Texture haloTex;
    haloTex.loadFromFile("img/gameover/light.png");
    Sprite halo(haloTex);
    halo.setOrigin(haloTex.getSize().x / 2, haloTex.getSize().y / 2);
    halo.setPosition(app.getSize().x / 2, app.getSize().y / 2 * 1.25);

    // Place letters
    for (decltype(this->texs)::size_type i = 0; i < this->texs.size(); i++) {
        Texture *letterTex = new Texture();
        letterTex->loadFromFile(this->GAMEOVER_PATH + this->texs.at(i) +
                                this->GAMEOVER_EXT);
        this->lettersSize = sf::Vector2f(letterTex->getSize());
        Sprite *s = new Sprite(*letterTex);
        s->setOrigin(letterTex->getSize().x / 2, letterTex->getSize().y / 2);
        this->letters.insert(this->letters.begin() + i, s);
    }

    // Move letters
    for (int i = 0; i < 18; i++) {
        this->letters.at(i)->setPosition(
            app.getSize().x / 2 - (1.3 * this->lettersSize.x) +
                (this->lettersSize.x / ((i % 9 > 3 ? 3.5 : 2.65))) * (i % 9) +
                (this->lettersSize.x / 1.7 * (i % 9 > 3 ? 1 : 0)),
            0 - (i % 9) * this->lettersSize.y * 0.5);
    }
    this->textLimitY = halo.getGlobalBounds().top / 2.0;

    // Place characters
    Texture p1DownTex;
    p1DownTex.loadFromFile("img/gameover/p1_down.png");
    this->playersDown.push_back(new Sprite(p1DownTex));
    Texture p2DownTex;

    if (this->mode == TWO_PLAYERS) {
        p2DownTex.loadFromFile("img/gameover/p2_down.png");
        this->playersDown.push_back(new Sprite(p2DownTex));

        this->playersDown[0]->setOrigin(0, p1DownTex.getSize().y / 2);
        this->playersDown[0]->setPosition(halo.getPosition());
        this->playersDown[1]->setOrigin(p2DownTex.getSize().x,
                                        p2DownTex.getSize().y / 2);
        this->playersDown[1]->setPosition(halo.getPosition());
    } else {
        this->playersDown[0]->setOrigin(p1DownTex.getSize().x / 2,
                                        p1DownTex.getSize().y / 2);
        this->playersDown[0]->setPosition(halo.getPosition());
    }

    // Insert sound
    SoundBuffer sfxBuffer;
    sfxBuffer.loadFromFile("sfx/gameover.ogg");
    Sound sfx(sfxBuffer);
    sfx.play();

    // ---------------- Main Loop ----------------
    while (true) {
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                return this->gotoScreen(EXIT_GAME);
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Escape) {
                return this->gotoScreen(TITLE_SCREEN);
            }
        }

        app.clear(this->m_bgcolor);
        app.draw(halo);
        this->updateSprite(halo.getPosition());
        for (auto p : this->playersDown) app.draw(*p);
        this->updateText();
        for (auto w : this->letters) app.draw(*w);
        app.display();
    }
    return this->gotoScreen(EXIT_GAME);
}
