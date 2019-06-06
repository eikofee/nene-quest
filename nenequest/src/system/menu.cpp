#include "menu.hpp"
#include "lifebar.hpp"

using namespace std;
using namespace sf;

Menu::Menu() { this->playing = false; }

short int Menu::validateMenu(short int menuIndex) {
    switch (menuIndex) {
        case 0:
            this->playing = true;
            return 1;
        case 1:
            return 2;
        default:
            return (-1);
    }
}

void Menu::cleanScreen() { }

int Menu::run(RenderWindow& app) {
    Event event;
    int menuIndex = 0;

    // ---------------- Logo ----------------
    Texture logoTex;
    logoTex.loadFromFile("img/titlescreen.png");
    logoTex.setSmooth(true);

    Sprite logo(logoTex);
    logo.setOrigin(Vector2f(logoTex.getSize().x / 2, logoTex.getSize().y / 2));
    logo.setPosition(app.getSize().x / 2, app.getSize().y / 2);
    logo.setScale(1.45, 1.45);
    logo.move(0, -200);

    Font font;
    font.loadFromFile("fonts/JapanSans100.ttf");
    Color menuTextColor(101, 45, 86, 255);

    // ---------------- Menu ----------------
    vector<Text *> menuButtons;

    Text onePlayerText(L"\u3072\u3068\u308A\u3067\u3042\u305D\u3076", font);
    menuButtons.push_back(&onePlayerText);

    Text twoPlayerText(L"\u3075\u305F\u308A\u3067\u3042\u305D\u3076", font);
    menuButtons.push_back(&twoPlayerText);

    Text exitText(L"\u304A\u308F\u308B", font);
    menuButtons.push_back(&exitText);

    for (unsigned int i = 0; i < menuButtons.size(); i++) {
        Text *t = menuButtons[i];
        t->setCharacterSize(this->TEXT_SIZE);
        t->setPosition(logo.getPosition());
        t->move(-300, 300 + i * 100);
        t->setFillColor(menuTextColor);
        t->setStyle(Text::Bold);
    }

    // ---------------- Selector ----------------
    Texture selectorTex;
    selectorTex.loadFromFile("img/cursor.png");
    selectorTex.setSmooth(true);

    Sprite selector(selectorTex);
    selector.setOrigin(Vector2f(selectorTex.getSize().x, 0));
    selector.setScale(0.3, 0.3);
    selector.setPosition(onePlayerText.getPosition());

    // ---------------- Main Loop ----------------
    while (true) {
        Vector2i localPosition = Mouse::getPosition(app);

        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) return (-1);

            // Keyboard handling
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Up:
                        menuIndex = (menuIndex - 1) % menuButtons.size();
                        break;
                    case Keyboard::Down:
                        menuIndex = (menuIndex + 1) % menuButtons.size();
                        break;
                    case Keyboard::Return:
                        return validateMenu(menuIndex);
                        break;
                    default:
                        break;
                }
                selector.setPosition(menuButtons[menuIndex]->getPosition());
            }
            // Mouse handling
            if (event.type == Event::MouseMoved) {
                for (unsigned int i = 0; i < menuButtons.size(); i++)
                    if (menuButtons[i]->getGlobalBounds().contains(
                            (float)localPosition.x, (float)localPosition.y))
                        menuIndex = i;
                selector.setPosition(menuButtons[menuIndex]->getPosition());
            }
            if (event.type == Event::MouseButtonPressed)
                return validateMenu(menuIndex);
        }

        app.clear(Color::White);
        app.draw(logo);
        app.draw(onePlayerText);
        app.draw(twoPlayerText);
        app.draw(exitText);
        app.draw(selector);
        app.display();
    }

    return (-1);
}
