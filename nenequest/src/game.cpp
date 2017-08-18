#include "../headers/game.hpp"
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace sf;

Game::Game() {

}

int Game::run(RenderWindow &app) {
	Event event;
	bool running = true;

	// Player
	Player player = Player(new Weapon(Axe), Vector2f(1000,400));
    bool moving_up = false;
    bool moving_down = false;
    bool moving_right = false;
    bool moving_left = false;

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

	Dragon dragon = Dragon(20, Vector2f(1000,200));
	BonusHp onigiri = BonusHp(BonusHp::ONIGIRI, Vector2f(1000,800));
    ItemWeapon sword = ItemWeapon(Sword, Vector2f(700,840));
    ItemWeapon axe = ItemWeapon(Axe, Vector2f(520,630));

    bonuses_hp.push_back(&onigiri);
    item_weapons.push_back(&axe);
    item_weapons.push_back(&sword);

    BreakableObject barrel = BreakableObject(Chest, Vector2f(520,630));

    //Clock
	Clock clock;

    // ---------------- Main Loop ----------------
	while(running) {

    float elapsedTime = clock.restart().asMilliseconds();

		while(app.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return (-1);
			}
			switch (event.type)
			{
			    case (Event::KeyPressed):
			        switch (event.key.code) {
                    case Keyboard::Up:
                        moving_up = true;
                        break;
                    case Keyboard::Down:
                        moving_down = true;
                        break;
                    case Keyboard::Right:
                        moving_right = true;
                        break;
                    case Keyboard::Left:
                        moving_left = true;
                        break;
                    default:
                        dragon.breathFire();
                        boar1.stun();
                        break;
			        }
			        break;
                case (Event::KeyReleased):
                    switch (event.key.code) {
                    case Keyboard::Up:
                        moving_up = false;
                        break;
                    case Keyboard::Down:
                        moving_down = false;
                        break;
                    case Keyboard::Right:
                        moving_right = false;
                        break;
                    case Keyboard::Left:
                        moving_left = false;
                        break;
                    default:
                        break;
			        }
                    break;
                case (Event::Closed):
                    app.close();
                    return -1;
                default:
                    break;
			}
		}

        if (moving_up) {
            player.move(Vector2f(0,-0.5), elapsedTime);
		} if (moving_down) {
            player.move(Vector2f(0,0.5), elapsedTime);
		} if (moving_right) {
            player.move(Vector2f(0.5,0), elapsedTime);
		} if (moving_left) {
            player.move(Vector2f(-0.5, 0), elapsedTime);
		}

        scroll(elapsedTime);

		boar1.update(elapsedTime);
		dragon.update(elapsedTime);
		background.update();

		app.clear(Color::White);
        app.draw(background);
		app.draw(boar1);
		app.draw(dragon);
		app.draw(life);
		app.draw(knightHead);
		app.draw(onigiri);
		app.draw(axe);
		app.draw(sword);
        app.draw(player);
        app.draw(barrel);

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
            if(players.at(i)->detectHit(*enemies.at(j))){
				life.decrease(enemies.at(j)->getAttackDamage());
            }
        }
        for(unsigned int j = 0; j < bonuses_hp.size(); j++){
            if(players.at(i)->detectHit(*enemies.at(j))){

                life.increase(bonuses_hp.at(j)->getHealedAmount());
                delete(bonuses_hp.at(j));
                bonuses_hp.erase(bonuses_hp.begin()+j);
            }
        }
        for(unsigned int j = 0; j < item_weapons.size(); j++){
            if(players.at(i)->detectHit(*item_weapons.at(j))){

                //item_weapons.push_back(new ItemWeapon(players.at(i)->getEquippedWeapon, players.at(i)->getPosition()))
                //player->equip();
                delete(item_weapons.at(j));
                item_weapons.erase(item_weapons.begin()+j);

            }
        }
    }
}

 void Game::scroll(float elapsedTime){
    for(BonusHp* var : bonuses_hp)
        var->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);
    for(ItemWeapon* var : item_weapons)
        var->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);

 }
