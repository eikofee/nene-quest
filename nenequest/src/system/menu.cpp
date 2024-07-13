#include "menu.hpp"
#include "lifebar.hpp"

using namespace std;
using namespace sf;

Menu::Menu() { }
Menu::~Menu() { }

class ActionPair {
  public:
    ActionPair(Text* t, ScreenState s) {
      button = t;
      screen = s;
    };
    Text* button;
    ScreenState screen;
};

ScreenState Menu::run(RenderWindow& app) {
    Event event;
    int menuIndex = 0;
    ScreenState selectedScreen = GAME_SCREEN;

    // ---------------- Logo ----------------
    Texture logoTex;
    logoTex.loadFromFile("img/titlescreen.png");
    logoTex.setSmooth(true);
    Sprite logo(logoTex);
		FloatRect logolb = logo.getLocalBounds();
    logo.setOrigin(logolb.width/2, logolb.height/2);
    logo.setPosition(app.getSize().x/2, app.getSize().y/2 - 200);
    logo.setScale(1.45, 1.45);

    // ---------------- Buttons ----------------
    Font font;
    font.loadFromFile("fonts/JapanSans100.ttf");
    Text p1button(L"\u3072\u3068\u308A\u3067\u3042\u305D\u3076", font);
    Text p2button(L"\u3075\u305F\u308A\u3067\u3042\u305D\u3076", font);
    Text exitButton(L"\u304A\u308F\u308B", font);

    array<ActionPair, 3> actionPairs = {
        ActionPair(&p1button, GAME_SCREEN),
        ActionPair(&p2button, GAME_OVER), // TODO : temporary, for tests
        ActionPair(&exitButton, EXIT_GAME)
    };

    for (unsigned int i=0; i<actionPairs.size(); i++) {
        Text* t = actionPairs[i].button;
        t->setCharacterSize(this->TEXT_SIZE);
        t->move(
            logo.getPosition().x - 300,
            logo.getPosition().y + 300 + i * 100
        );
        t->setFillColor(Color(101, 45, 86, 255));
        t->setStyle(Text::Bold);
    }

    // ---------------- Cursor ----------------
    Texture cursorTex;
    cursorTex.loadFromFile("img/cursor.png");
    cursorTex.setSmooth(true);

    Sprite cursor(cursorTex);
    cursor.setOrigin(Vector2f(cursorTex.getSize().x, 0));
    cursor.setScale(0.3, 0.3);
    cursor.setPosition(p1button.getPosition());

    // ---------------- Main Loop ----------------
    while (true) {
        Vector2i mousePos = Mouse::getPosition(app);

        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                return EXIT_GAME;

            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Up:
                      menuIndex = (menuIndex-1)%actionPairs.size();
                      break;
                    case Keyboard::Down:
                      menuIndex = (menuIndex+1)%actionPairs.size();
                      break;
                    case Keyboard::Return:
                      return actionPairs[menuIndex].screen;
                      break;
                    default:
                      break;
                }
                cursor.setPosition(actionPairs[menuIndex].button->getPosition());
            }

            if (event.type == Event::MouseMoved) {
                for (auto action : actionPairs) {
                    if (action.button->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cursor.setPosition(action.button->getPosition());
                        selectedScreen = action.screen;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed)
                return selectedScreen;
        }

        app.clear(Color::White);
        app.draw(logo);
        for (auto action : actionPairs)
            app.draw(*action.button);
        app.draw(cursor);
        app.display();
    }

    return EXIT_GAME;
}
