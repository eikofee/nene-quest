#include "victory.hpp"

#include <math.h>

#include <vector>

#include "textures.hpp"
#include "world.hpp"

using namespace std;
using namespace sf;

void Victory::clearAll() { }

ScreenState Victory::run(RenderWindow &app) {
    Event event;
    Vector2f center(app.getSize().x / 2, app.getSize().y / 2);

    // Halo
    string haloPath = "img/gameover/light.png";
    const Texture &haloTex = getTexture(haloPath);
    Sprite halo(haloTex);
    halo.setOrigin(haloTex.getSize().x / 2, haloTex.getSize().y / 2);
    halo.setPosition(center.x, center.y * 1.25);

    // "Congratulations!", in the menu's font
    Font font;
    font.loadFromFile("fonts/JapanSans100.ttf");
    Text text(L"おめでとう！", font, TEXT_SIZE);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);
    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2,
                   bounds.top + bounds.height / 2);
    text.setPosition(center.x, center.y * 0.4);

    // The knights, standing in the halo (first frame of their sheet)
    vector<Sprite> knights;
    vector<string> paths = {"img/player1.png"};
    if (World::isTwoPlayer()) paths.push_back("img/player2.png");
    for (unsigned int i = 0; i < paths.size(); i++) {
        const Texture &tex = getTexture(paths[i]);
        Sprite knight(tex, IntRect(0, 0, tex.getSize().x / 2,
                                   tex.getSize().y / 3));
        FloatRect kb = knight.getLocalBounds();
        knight.setOrigin(kb.width / 2, kb.height);
        float offset = (i - (paths.size() - 1) / 2.f) * kb.width * 1.2f;
        knight.setPosition(halo.getPosition().x + offset,
                           halo.getPosition().y + kb.height / 2);
        knights.push_back(knight);
    }
    vector<float> groundY;
    for (auto &k : knights) groundY.push_back(k.getPosition().y);

    Clock clock;
    // ---------------- Main Loop ----------------
    while (true) {
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                return this->gotoScreen(EXIT_GAME);
            if (event.type == Event::KeyPressed &&
                (event.key.code == Keyboard::Escape ||
                 event.key.code == Keyboard::Enter))
                return this->gotoScreen(TITLE_SCREEN);
        }

        // The knights hop for joy, one after the other
        float t = clock.getElapsedTime().asSeconds();
        for (unsigned int i = 0; i < knights.size(); i++)
            knights[i].setPosition(
                knights[i].getPosition().x,
                groundY[i] - HOP_HEIGHT * fabs(sin(t * HOP_SPEED / 2 + i)));

        app.clear(this->m_bgcolor);
        app.draw(halo);
        for (auto &k : knights) app.draw(k);
        app.draw(text);
        app.display();
    }
    return this->gotoScreen(EXIT_GAME);
}
