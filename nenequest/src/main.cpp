#include <SFML/Graphics.hpp>
#include "../headers/screens.hpp"
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	vector<Screen*> screens;
	int selectedScreen = 0;

	RenderWindow app(VideoMode::getDesktopMode(), "Nene Quest", Style::Close | Style::Titlebar);


	Menu s0;
	screens.push_back(&s0);
	Game s1;
	screens.push_back(&s1);

	while (selectedScreen >= 0) {
		selectedScreen = screens[selectedScreen]->run(app);
	}

	return EXIT_SUCCESS;
}
