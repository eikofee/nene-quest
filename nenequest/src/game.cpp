#include "../headers/game.hpp"

using namespace std;
using namespace sf;

Game::Game() {

}

int Game::run(RenderWindow &app) {
	Event event;
	bool running = true;


	// LifeBar
    life = LifeBar(100);
	life.setPosition(300, 100);

	Texture knightHeadTex;
	knightHeadTex.loadFromFile("img/icon_p1.png");
	Sprite knightHead(knightHeadTex);
	knightHead.setOrigin(knightHeadTex.getSize().x/2, knightHeadTex.getSize().x/2);
	knightHead.setPosition(life.getPosition());
	knightHead.move(-life.LIFEBAR_WIDTH/2, -10);

	// Background
    Background background = Background(app.getSize());

	//Test cloud
	//RandomCloud cloud;
	//cloud.setPosition(500, 500);
	//cloud.generateBorder();

	Boar boar1 = Boar(app.getSize(), Vector2f(app.getSize().x - 100, app.getSize().y/2), Vector2f(-1,0));
	Dragon dragon = Dragon(Vector2f(1000,500));

    //Clock
	Clock clock;

    // ---------------- Main Loop ----------------
	while(running) {

    float elapsedTime = clock.restart().asMilliseconds();

		while(app.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return (-1);
			}
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
                    case Keyboard::Up:
                        boar1.stun();
                        break;
                    case Keyboard::Down:
                        break;
                    default:
                        break;
				}
			}
		}

		boar1.update(elapsedTime);
		dragon.update(elapsedTime);
		background.update();

		app.clear(Color::White);
        app.draw(background);
		app.draw(boar1);
		app.draw(dragon);
		app.draw(life);
		app.draw(knightHead);

		//Test cloud part 2
		//cloud.update();
		//if (cloud.isAlive())
		//	app.draw(cloud);
		
		
		app.display();

	}

	return (-1);
}

//Collision detection
void Game::checkCollision(){

    for(unsigned int i = 0; i < players.size(); i++){
        for(unsigned int j = 0; j < enemies.size(); j++){
            if(players.at(i).detectHit(enemies.at(j))){
                life.decrease(enemies.at(j).getAttackDamage());
            }
        }
        /*for(int j = 0; j < onigiris.size(); j++){
            if(players.at(i)->detectHit(enemies.at(j))){
                life.decrease(enemies.at(j).getAttackDamage());
            }
        }
        for(int j = 0; j < weapons.size(); j++){
            if(players.at(i)->detectHit(enemies.at(j))){

            }
        }*/
    }
}
