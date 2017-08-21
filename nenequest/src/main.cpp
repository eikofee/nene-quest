#include <SFML/Graphics.hpp>
#include "../headers/screens.hpp"
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	vector<Screen*> screens;
	int selectedScreen = 0;

	RenderWindow app(VideoMode::getDesktopMode(), "Nene Quest", Style::Close | Style::Titlebar);
    app.setFramerateLimit(60);

	screens.push_back(new Menu);
	screens.push_back(new Game);
	screens.push_back(new GameOver);

	while (selectedScreen >= 0)
		selectedScreen = screens[selectedScreen]->run(app);

	return EXIT_SUCCESS;
}
