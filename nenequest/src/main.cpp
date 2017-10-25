#include <SFML/Graphics.hpp>
#include "../headers/screens.hpp"
#include "../headers/config.hpp"
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	vector<Screen*> screens;
	int selectedScreen = 0;
	
	sf::VideoMode mode = VideoMode::getDesktopMode();
	Uint32 style = Style::Close | Style::Titlebar;
	if (DSP_FULLSCREEN)
		style = style | sf::Style::Fullscreen;
	if (DSP_RESOLUTION == 720)
		mode = VideoMode::VideoMode(1280, 720);

	RenderWindow app(mode, "Nene Quest", style);
    app.setFramerateLimit(DSP_FPS_LIMIT);

	screens.push_back(new Menu);
	screens.push_back(new Game);
	screens.push_back(new GameOver(ONE_PLAYER));
	screens.push_back(new GameOver(TWO_PLAYER));

	while (selectedScreen >= 0)
		selectedScreen = screens[selectedScreen]->run(app);
		
	return EXIT_SUCCESS;
}
