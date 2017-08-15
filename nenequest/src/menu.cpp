#include "../headers/menu.hpp"

using namespace std;
using namespace sf;

Menu::Menu() {
	playing = false;
}

int Menu::run(RenderWindow &app) {
	Event event;
	bool running = true;
	int menuIndex = 0;

	// ---------------- Logo ----------------
	Texture logoTex;
    logoTex.loadFromFile("img/titlescreen.png");
    logoTex.setSmooth(true);

    Sprite logo;
    logo.setTexture(logoTex);
    logo.setOrigin(Vector2f(logoTex.getSize().x/2, logoTex.getSize().y/2));
    logo.setPosition(app.getSize().x/2, app.getSize().y/2);
    logo.move(0, -200);

    Font font;
    font.loadFromFile("fonts/JapanSans100.ttf");
    Color menuTextColor(101, 45, 86, 255);

    // ---------------- Menu ----------------
    vector<Text*> menuButtons;
    const int TEXT_SIZE = 90;

    Text onePlayerText;
    onePlayerText.setString(L"ひとりであそぶ");
    menuButtons.push_back(&onePlayerText);

    Text twoPlayerText;
    twoPlayerText.setString(L"ふたりであそぶ");
    menuButtons.push_back(&twoPlayerText);

    Text exitText;
    exitText.setString(L"おわる");
    menuButtons.push_back(&exitText);

    for (int i=0; i<menuButtons.size(); i++) {
        Text* t = menuButtons[i];
        t->setFont(font);
        t->setCharacterSize(TEXT_SIZE);
        t->setPosition(logo.getPosition());
        t->move(-300, 300);
        t->move(0, i*100);
        t->setFillColor(menuTextColor);
        t->setStyle(Text::Bold);
    }

    // Selector
    Texture selectorTex;
    selectorTex.loadFromFile("img/cursor.png");
    selectorTex.setSmooth(true);

    Sprite selector;
    selector.setTexture(selectorTex);
    selector.setOrigin(Vector2f(selectorTex.getSize().x, 0));
    selector.setScale(0.3, 0.3);
    selector.setPosition(onePlayerText.getPosition());

    // ---------------- Main Loop ----------------
	while(running) {
		while(app.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return (-1);
			}
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
                    case Keyboard::Up:
                        menuIndex = (menuIndex-1)%menuButtons.size();
                        break;
                    case Keyboard::Down:
                        menuIndex = (menuIndex+1)%menuButtons.size();
                        break;
                    case Keyboard::Return:
                        if (menuIndex == 0) {
                            playing = true;
                            return 1;
                        }
                        else {
                            return (-1);
                        }
                        break;
                    default:
                        break;
				}
				selector.setPosition(menuButtons[menuIndex]->getPosition());
			}
		}

		app.clear(Color(252, 251, 253, 255));
		app.draw(logo);
		app.draw(onePlayerText);
		app.draw(twoPlayerText);
		app.draw(exitText);
		app.draw(selector);
		app.display();
	}

	return (-1);
}
