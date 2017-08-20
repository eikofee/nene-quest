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
    players.push_back(&player);

	// LifeBar
    //life = LifeBar(100);
	//life.setPosition(300, 100);

    /**
        FIXME : Kostia, déplacer le code de knightHead dans la classe "LifeBar"
    **/
	Texture knightHeadTex;
	knightHeadTex.loadFromFile("img/icon_p1.png");
	Sprite knightHead(knightHeadTex);

	knightHead.setOrigin(knightHeadTex.getSize().x/2, knightHeadTex.getSize().x/2);
	knightHead.setPosition(player.getLife()->getPosition());
	knightHead.move(-player.getLife()->LIFEBAR_WIDTH/2, -10);

	// Background
    Background background = Background(app.getSize());

	//Test cloud
	//RandomCloud cloud;
	//cloud.setPosition(500, 500);
	//cloud.generateBorder();

	Boar* boar1 = new Boar(Vector2f(app.getSize().x - 100, app.getSize().y/2));
	Dragon* dragon = new Dragon(20, Vector2f(1000,200));
	BonusHp* onigiri = new BonusHp(BonusHp::ONIGIRI, Vector2f(1000,800));
    ItemWeapon* sword = new ItemWeapon(Sword, Vector2f(800,600));

    bonuses_hp.push_back(onigiri);
    item_weapons.push_back(sword);
    item_weapons.push_back(new ItemWeapon(GreatSword, Vector2f(300,630)));
    enemies.push_back(dragon);
    enemies.push_back(boar1);


    BreakableObject* barrel = new BreakableObject(Chest, Vector2f(520,630));
    breakable_objects.push_back(barrel);
    breakable_objects.push_back(new BreakableObject(Barrel, Vector2f(1200, 600)));


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
                    case Keyboard::Space:
                        player.attack();
                        break;
                    default:
                        dragon->breathFire();
                        boar1->stun();
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

        //scroll(elapsedTime);

        boar1->update(elapsedTime);
        dragon->update(elapsedTime);
        background.update();


        Vector2f playerSpeed = Vector2f(0,0);

        if (moving_up) {
            playerSpeed.y -= PLAYER_SPEED;
        } if (moving_down) {
            playerSpeed.y += PLAYER_SPEED;
        } if (moving_right) {
            playerSpeed.x += PLAYER_SPEED;
        } if (moving_left) {
            playerSpeed.x -= PLAYER_SPEED;
        }

        if(playerSpeed.x != 0){
            player.move(Vector2f(playerSpeed.x, 0), elapsedTime);
            if(playerIsColliding(&player)){
                //Do/While in case the player collide several object at the same time
                do{
                    BreakableObject* tmp = getCollidingObject(&player);
                    if(playerSpeed.x > 0){
                        player.setPosition(tmp->getPosition().x - player.getHitbox().getGlobalBounds().width -1, player.getPosition().y);
                    }
                    else{
                        player.setPosition(tmp->getPosition().x + tmp->getHitbox().getGlobalBounds().width +1, player.getPosition().y);
                    }

                }while(playerIsColliding(&player));
            }
        }

        if(playerSpeed.y != 0){
            player.move(Vector2f(0, playerSpeed.y), elapsedTime);
            if(playerIsColliding(&player)){
                //Do/While in case the player collide several object at the same time
                do{
                    BreakableObject* tmp = getCollidingObject(&player);
                    if(playerSpeed.y > 0){
                        player.setPosition(player.getPosition().x, tmp->getPosition().y - player.getHitbox().getGlobalBounds().height*2 - 1);
                    }
                    else{
                        player.setPosition(player.getPosition().x, tmp->getPosition().y + tmp->getHitbox().getGlobalBounds().height - player.getHitbox().getGlobalBounds().height +1);
                    }

                }while(playerIsColliding(&player));
            }
        }



        checkCollision(elapsedTime, app.getSize());

        app.clear(Color::White);
        app.draw(background);
        app.draw(knightHead);

        for(BreakableObject* var : breakable_objects)
            app.draw(*var);

        for(BonusHp* var : bonuses_hp)
            app.draw(*var);

        for(ItemWeapon* var : item_weapons)
            app.draw(*var);

        for(Enemy* var : enemies)
            app.draw(*var);

        for(Player* var : players)
            app.draw(*var);



        //Test cloud part 2
        //cloud.update();
        //if (cloud.isAlive())
        //	app.draw(cloud);

        app.display();

	}

	return (-1);
}

//Collision detection
void Game::checkCollision(float elapsedTime, Vector2u windowSize){

    //Collisions with enemies
    for(unsigned int i = 0; i < players.size(); i++){
        if(player_invulnerability_timer <= 0){
            for(unsigned int j = 0; j < enemies.size(); j++){
                if(players.at(i)->detectHit(*enemies.at(j))){
                    players.at(i)->getLife()->decrease(enemies.at(j)->getAttackDamage());
                    player_invulnerability_timer = 200;
                }
            }
        }
        else{
            player_invulnerability_timer -= elapsedTime;
        }

        //Collisions with bonus hp
        for(unsigned int j = 0; j < bonuses_hp.size(); j++){

            //Check if the item is still on screen
            if(!bonuses_hp.at(j)->isOnScreen(windowSize)){
                delete(bonuses_hp.at(j));
                bonuses_hp.erase(bonuses_hp.begin()+j);
            }
            //Check for collisions between the player and the item
            else if(players.at(i)->detectHit(*bonuses_hp.at(j))){

                players.at(i)->getLife()->increase(bonuses_hp.at(j)->getHealedAmount());
                delete(bonuses_hp.at(j));
                bonuses_hp.erase(bonuses_hp.begin()+j);
            }
        }

        //Collisions with weapon items
        for(unsigned int j = 0; j < item_weapons.size(); j++){
            //Check if the item is still on screen
            if(!item_weapons.at(j)->isOnScreen(windowSize)){
                delete(item_weapons.at(j));
                item_weapons.erase(item_weapons.begin()+j);
            }

            //Check for collisions between the player and the item
            else if(players.at(i)->detectHit(*item_weapons.at(j))){

                if(! item_weapons.at(j)->checkIfDropped()){

                    WeaponType weaponType = item_weapons.at(j)->getWeaponType();
                    if(players.at(i)->getWeapon()->getWeaponType() != weaponType){

                        //Drop old weapon
                        ItemWeapon* tmp = new ItemWeapon(players.at(i)->getWeapon()->getWeaponType(), item_weapons.at(j)->getPosition());

                        //setDropped used to prevent the player from interacting with the item again when he's still standing on it
                        tmp->setDropped(true);
                        item_weapons.push_back(tmp);
                        delete(item_weapons.at(j));
                        item_weapons.erase(item_weapons.begin()+j);

                        //Equip new weapon
                        players.at(i)->equip(new Weapon(weaponType));

                    }
                }
            }
            else{
                item_weapons.at(j)->setDropped(false);
            }
        }

        //Collision with breakable objects
        for(unsigned int j = 0; j < breakable_objects.size(); j++){

            //Check if the object is still on screen
            if(!breakable_objects.at(j)->isOnScreen(windowSize)){
                delete(breakable_objects.at(j));
                breakable_objects.erase(breakable_objects.begin()+j);
            }
            //Check for collisions between the player and the object
            else if(players.at(i)->detectHit(*breakable_objects.at(j))){
                /*Bonus* tmp;
                if(tmp = breakable_objects.at(j)->getDrops()){
                    if(tmp->getBonusType() == Item_Onigiri)
                        bonuses_hp.push_back((BonusHp*)tmp);
                    else
                        item_weapons.push_back((ItemWeapon*)tmp);
                }

                delete(breakable_objects.at(j));
                breakable_objects.erase(breakable_objects.begin()+j);*/
                //blockPlayer(players.at(i));
            }
        }

    }
}

 void Game::scroll(float elapsedTime){
    for(BonusHp* var : bonuses_hp)
        var->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);
    for(ItemWeapon* var : item_weapons)
        var->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);
    for(BreakableObject* var : breakable_objects)
        var->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);

    //Check if player is pushed by the scrolling
    for(Player* player : players){
        if(playerIsColliding(player)){
            //Move the player of 1 pixel to the left until he isn't in collision within any object
            do{
                player->move(Vector2f(-1/elapsedTime, 0), elapsedTime);

                //If the scrolling pushes the player into the border of the screen, destroy the item pushing him and damage the player
                if(player->getPosition().x <= 0){
                    for(unsigned int j = 0;j < breakable_objects.size();j++){
                        if(player->detectHit(*breakable_objects.at(j)))
                            delete(breakable_objects.at(j));
                            breakable_objects.erase(breakable_objects.begin()+j);
                            life.decrease(SCROLLING_DAMAGE);
                            player->move(Vector2f(1/elapsedTime, 0), elapsedTime);
                    }

                }

            }while(playerIsColliding(player));
        }
    }
 }

 bool Game::playerIsColliding(Player* p){
    for(unsigned int j = 0; j < breakable_objects.size(); j++){
        if(p->detectHit(*breakable_objects.at(j))){
            return true;
        }
    }
    return false;

 }

 BreakableObject* Game::getCollidingObject(Player* p){
    for(BreakableObject* obj : breakable_objects)
        if(p->detectHit(*obj))
            return obj;

    return NULL;
 }
