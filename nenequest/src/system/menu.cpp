#include "menu.hpp"
#include "lifebar.hpp"

using namespace std;
using namespace sf;

Menu::Menu() { }

Menu::~Menu() { }

ScreenState Menu::run(RenderWindow& app) {
    Event event;
    int menuIndex = 0;
    ScreenState selectedByMouse = GAME_SCREEN;

    // ---------------- Logo ----------------
    Texture logoTex;
    logoTex.loadFromFile("img/titlescreen.png");
    logoTex.setSmooth(true);
    Sprite logo(logoTex);
    logo.setOrigin(Vector2f(logoTex.getSize().x/2, logoTex.getSize().y/2));
    logo.setPosition(app.getSize().x/2, app.getSize().y/2);
    logo.setScale(1.45, 1.45);
    logo.move(0, -200);

    // ---------------- Buttons ----------------
    Font font;
    font.loadFromFile("fonts/JapanSans100.ttf");

    Text p1button(L"\u3072\u3068\u308A\u3067\u3042\u305D\u3076", font);
    Text p2button(L"\u3075\u305F\u308A\u3067\u3042\u305D\u3076", font);
    Text exitButton(L"\u304A\u308F\u308B", font);

    // array<pair<Text*, ScreenState>, 3> buttons = {
    vector<pair<Text*, ScreenState>> buttons = {
        make_pair(&p1button, GAME_SCREEN),
        make_pair(&p2button, GAME_OVER), // TODO : temporary, for tests
        make_pair(&exitButton, EXIT_GAME)
    };

    for (unsigned int i=0; i<3; i++) {
        Text* t = buttons[i].first;
        t->setCharacterSize(this->TEXT_SIZE);
        t->setPosition(logo.getPosition());
        t->move(-300, 300 + i * 100);
        t->setFillColor(Color(101, 45, 86, 255));
        t->setStyle(Text::Bold);
    }

    // ---------------- Selector ----------------
    Texture selectorTex;
    selectorTex.loadFromFile("img/cursor.png");
    selectorTex.setSmooth(true);

    Sprite selector(selectorTex);
    selector.setOrigin(Vector2f(selectorTex.getSize().x, 0));
    selector.setScale(0.3, 0.3);
    selector.setPosition(p1button.getPosition());

    // ---------------- Main Loop ----------------
    while (true) {
        Vector2i mousePos = Mouse::getPosition(app);

        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) return EXIT_GAME;

            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Up: menuIndex = (menuIndex-1)%buttons.size(); break;
                    case Keyboard::Down: menuIndex = (menuIndex+1)%buttons.size(); break;
                    case Keyboard::Return: return buttons[menuIndex].second; break;
                    default: break;
                }
                selector.setPosition(buttons[menuIndex].first->getPosition());
            }

            if (event.type == Event::MouseMoved) {
                for (auto b : buttons) {
                    if (isSelected(b.first, mousePos.y)) {
                        selector.setPosition(b.first->getPosition());
                        selectedByMouse = b.second;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed)
                return selectedByMouse;
        }

        app.clear(Color::White);
        app.draw(logo);
        for (auto b : buttons)
            app.draw(*b.first);
        app.draw(selector);
        app.display();
    }

    return EXIT_GAME;
}

bool Menu::isSelected(Text* button, int mouseY) {
    return button->getGlobalBounds().top >= (float)mouseY && 
    button->getGlobalBounds().top-button->getGlobalBounds().height <= (float)mouseY;
}
