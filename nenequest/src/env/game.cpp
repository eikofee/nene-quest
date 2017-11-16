#include <game.hpp>
#include <world.hpp>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace sf;

Game::Game() {
	// Final game objects (should only include Game, Players, LevelManagers and other UI events)
	this->manager = new LevelManager(this);
	this->parser = new LevelParser();
	this->parser->setLevelManager(this->manager);
	this->parser->initialize();
	this->parser->setLevelFilesPath("levels");
}

int Game::run(RenderWindow &app) {
	Event event;
    Background background = Background(app.getSize());
	this->manager->setBackground(&background);

	//Load Level
	this->parser->parseFile("level0.nnq");

	//Testing objects////////////
    bridge = new BridgePit(300, app.getSize().y-background.getSkyHeight(), app.getSize().y);
	World::addEntity(bridge);

	//Boar* boar1 = new Boar(Vector2f(app.getSize().x - 1010, app.getSize().y/2));
	//Dragon* dragon = new Dragon(Vector2f(1000,400));
	//BonusHp* onigiri = new BonusHp(BonusHp::ONIGIRI, Vector2f(1000,800));
    //ItemWeapon* sword = new ItemWeapon(Sword, Vector2f(800,600));
    //bonuses_hp.push_back(onigiri);
    //item_weapons.push_back(sword);
    //item_weapons.push_back(new ItemWeapon(GreatSword, Vector2f(300,630)));
    //enemies.push_back(dragon);
	//enemies.push_back(boar1);
    //BreakableObject* barrel = new BreakableObject(Chest, Vector2f(520,630));
    //breakable_objects.push_back(barrel);
    //breakable_objects.push_back(new BreakableObject(Barrel, Vector2f(700,630)));
    //Arrow arrow = Arrow(Vector2f(100, 700), 700);
    /////////////////////////////
	
	Clock clock;

    // ---------------- Main Loop ----------------
	while(true) {
		float elapsedTime = clock.restart().asMilliseconds();

		while(app.pollEvent(event)) {
			if (event.type == Event::Closed)
				return (-1);
			manageInputs(event, PlayerID::PLAYER1,
				Keyboard::Up,
				Keyboard::Down,
				Keyboard::Left,
				Keyboard::Right,
				Keyboard::Space
			);

			if (this->players.size() == 2)
				manageInputs(event, PlayerID::PLAYER2,
					Keyboard::Z,
					Keyboard::S,
					Keyboard::Q,
					Keyboard::D,
					Keyboard::H
				);
		}

		World::setElapsedTime(elapsedTime);
		World::updateEntities();

		//scroll(elapsedTime, app.getSize());
		
		for (Player* p : this->players) {
			p->update(elapsedTime);
			//playerMove(p, elapsedTime, app.getSize(), background.getSkyHeight());
		}

		this->manager->update();
		background.update();
		//arrow.update(elapsedTime);
		//checkCollision(elapsedTime, app.getSize());

		app.clear(Color::White);
		app.draw(background);
		//app.draw(*bridge);
		World::render(app);

		//drawWithDepth(&app);
		//app.draw(arrow);
		app.display();
	}

	return (-1);
}

// Temporary solution for input management
void Game::manageInputs(
	sf::Event e,
	PlayerID id,
	Keyboard::Key up,
	Keyboard::Key down,
	Keyboard::Key left,
	Keyboard::Key right,
	Keyboard::Key attack) {

	this->players = World::getPlayers();
	if (e.type == Event::KeyPressed) {
		if (e.key.code == up)
			this->players.at(id)->moving_up = true;
		else if (e.key.code == down)
				this->players.at(id)->moving_down = true;
		else if (e.key.code == right)
			this->players.at(id)->moving_right = true;
		else if (e.key.code == left)
			this->players.at(id)->moving_left = true;
		else if (e.key.code == attack) {
			this->players.at(id)->attack();
			if (!this->players.at(id)->isShooting())
				this->players.at(id)->fireArrow();
		}
	}
	else if (e.type == Event::KeyReleased) {
		if (e.key.code == up)
			this->players.at(id)->moving_up = false;
		else if (e.key.code == down)
			this->players.at(id)->moving_down = false;
		else if (e.key.code == right)
			this->players.at(id)->moving_right = false;
		else if (e.key.code == left)
			this->players.at(id)->moving_left = false;
		else if (e.key.code == attack)
			this->players.at(id)->setShootingState(false);
	}
}

//Collision detection
//TODO: Move this somewhere else (World class)
//void Game::checkCollision(float elapsedTime, Vector2u windowSize){
//
//    for(unsigned int i = 0; i < players.size(); i++){
//
//        for(Arrow* arrow : players.at(i)->getArrows()){
//            for(unsigned int j = 0; j < enemies.size(); j++){
//                if(enemies.at(j)->detectHit(arrow)){
//                    enemies.at(j)->take_damage(Arrow::ARROW_DAMAGE);
//                    arrow->kill();
//                }
//            }
//            for(unsigned int j = 0; j < breakable_objects.size(); j++){
//                if(arrow->detectHit(breakable_objects.at(j))){
//                    arrow->kill();
//
//                    if(Bonus* tmp = breakable_objects.at(j)->getDrops()){
//                        Vector2f dropPosition = Vector2f(breakable_objects.at(j)->getHitbox().getGlobalBounds().left
//                                                        , breakable_objects.at(j)->getHitbox().getGlobalBounds().top + breakable_objects.at(j)->getHitbox().getGlobalBounds().height -100);
//                        dropItem(tmp, dropPosition);
//                    }
//
//
//                    delete(breakable_objects.at(j));
//                    breakable_objects.erase(breakable_objects.begin()+j);
//
//                }
//            }
//        }
//        if(!players.at(i)->isJumping()){
//
//            //Collisions with enemies
//            if(player_invulnerability_timer <= 0){
//                for(unsigned int j = 0; j < enemies.size(); j++){
//                    if(enemies.at(j)->detectHit(players.at(i))){
//                        players.at(i)->getLife()->decrease(enemies.at(j)->getAttackDamage());
//                        player_invulnerability_timer = 200;
//                        break;
//                    }
//                    if(enemies.at(j)->getEnemyType() == Enemy_Dragon){
//                       vector<Flame*> flames = ((Dragon*)enemies.at(j))->getFlames();
//                       for(Flame* flame : flames){
//                            if(players.at(i)->detectHit(flame)){
//                               players.at(i)->getLife()->decrease(Flame::FLAMES_DAMAGE);
//                               player_invulnerability_timer = 200;
//                               break;
//                            }
//                       }
//                    }
//
//                }
//            }
//            else{
//                player_invulnerability_timer -= elapsedTime;
//            }
//
//            //Collisions with bonus hp
//            for(unsigned int j = 0; j < bonuses_hp.size(); j++){
//
//                //Check for collisions between the player and the item
//                if(players.at(i)->detectHit(bonuses_hp.at(j))){
//
//                    players.at(i)->getLife()->increase(bonuses_hp.at(j)->getHealedAmount());
//                    delete(bonuses_hp.at(j));
//                    bonuses_hp.erase(bonuses_hp.begin()+j);
//                }
//            }
//
//            //Collisions with weapon items
//            for(unsigned int j = 0; j < item_weapons.size(); j++){
//
//                //Check for collisions between the player and the item
//                if(players.at(i)->getLastDroppedItem() == NULL || !players.at(i)->detectHit(players.at(i)->getLastDroppedItem())){
//                    players.at(i)->setLastDroppedItem(NULL);
//                    if(item_weapons.at(j)->detectHit(players.at(i))){
//
//                        WeaponType weaponType = item_weapons.at(j)->getWeaponType();
//                        if(players.at(i)->getWeapon()->getWeaponType() != weaponType){
//
//                            //Drop old weapon
//                            ItemWeapon* tmp = new ItemWeapon(players.at(i)->getWeapon()->getWeaponType(), item_weapons.at(j)->getPosition());
//
//                            //setDropped used to prevent the player from interacting with the item again when he's still standing on it
//                            item_weapons.push_back(tmp);
//                            players.at(i)->setLastDroppedItem(tmp);
//
//                            //If an other player is standing on the item, change it's last dropped item
//                            for(Player* var : players)
//                                if(var->getLastDroppedItem() == item_weapons.at(j))
//                                    var->setLastDroppedItem(tmp);
//
//                            delete(item_weapons.at(j));
//                            item_weapons.erase(item_weapons.begin()+j);
//
//                            //Equip new weapon
//                            players.at(i)->equip(new Weapon(weaponType));
//
//                        }
//                    }
//                }
//            }
//        }
//    }
//}

//Some of the code here should be moved into entities' or in a World class
 //void Game::scroll(float elapsedTime, Vector2u windowSize){
 //   for(unsigned int j = 0; j < item_weapons.size(); j++){
 //       item_weapons.at(j)->move(Vector2f(SCROLL_SPEED, 0));
 //       //Check if the item is still on screen
 //       if(!item_weapons.at(j)->isOnScreen(windowSize)){
 //           delete(item_weapons.at(j));
 //           item_weapons.erase(item_weapons.begin()+j);
 //       }
 //   }
 //   for(unsigned int j = 0; j < bonuses_hp.size(); j++){
 //       bonuses_hp.at(j)->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);
 //       //Check if the item is still on screen
 //       if(!bonuses_hp.at(j)->isOnScreen(windowSize)){
 //           delete(bonuses_hp.at(j));
 //           bonuses_hp.erase(bonuses_hp.begin()+j);
 //       }
 //   }
 //   for(unsigned int j = 0; j < breakable_objects.size(); j++){
 //       breakable_objects.at(j)->move(Vector2f(SCROLL_SPEED, 0), elapsedTime);
 //       //Check if the item is still on screen
 //       if(!breakable_objects.at(j)->isOnScreen(windowSize)){
 //           delete(breakable_objects.at(j));
 //           breakable_objects.erase(breakable_objects.begin()+j);
 //       }
 //   }

 //   //Check if player is pushed by the scrolling
 //   for(Player* player : players){
 //       if(playerIsColliding(player)){
 //           //Move the player of 1 pixel to the left until he isn't in collision within any object
 //           do{
 //               player->setPosition(player->getPosition().x -1, player->getPosition().y);

 //               //If the scrolling pushes the player into the border of the screen, destroy the item pushing him and damage the player
 //               if(player->getPosition().x <= 0){
 //                   for(unsigned int j = 0;j < breakable_objects.size();j++){
 //                       if(player->detectHit(breakable_objects.at(j)))
 //                           delete(breakable_objects.at(j));
 //                           breakable_objects.erase(breakable_objects.begin()+j);
 //                           life.decrease(SCROLLING_DAMAGE);
 //                           player->setPosition(0,player->getPosition().y);
 //                   }

 //               }

 //           }while(playerIsColliding(player));
 //       }
 //   }
 //}

//Unused
bool Game::playerIsColliding(Player* p){
    for (unsigned int j=0; j < breakable_objects.size(); j++)
        if (p->detectHit(breakable_objects.at(j)))
            return true;
    return false;
 }

 BreakableObject* Game::getCollidingObject(Player* p){
    for (BreakableObject* obj : breakable_objects)
        if (p->detectHit(obj))
            return obj;
    return NULL;
 }

//Deprecated
//void Game::playerMove(Player* player, float elapsedTime, Vector2u windowSize, float skyHeight){
/*    for(Player* player : players){
         Vector2f playerSpeed = Vector2f(0,0);

        if (player->moving_up) {
            playerSpeed.y -= PLAYER_SPEED;
        } if (player->moving_down) {
            playerSpeed.y += PLAYER_SPEED;
        } if (player->moving_right) {
            playerSpeed.x += PLAYER_SPEED;
        } if (player->moving_left) {
            playerSpeed.x -= PLAYER_SPEED;
        }

        if(playerSpeed.x != 0){
            player->move(Vector2f(playerSpeed.x, 0), elapsedTime);

            //Check if the player isn't leaving the screen
            if(player->getPosition().x + player->getHitbox().getLocalBounds().width > windowSize.x)
                player->setPosition(windowSize.x - player->getHitbox().getGlobalBounds().width, player->getPosition().y);
            else if(player->getPosition().x + playerSpeed.x*elapsedTime < 0)
                player->setPosition(0, player->getPosition().y);

            if(bridge->detectHit(player)){
                if(playerSpeed.x > 0)
                    player->setPosition(bridge->getSpriteBounds().left - player->getHitbox().getGlobalBounds().width, player->getPosition().y);
                else
                    player->setPosition(bridge->getSpriteBounds().left +  bridge->getSpriteBounds().width, player->getPosition().y);
            }

            if(playerIsColliding(player)){
                //Do/While in case the player collide several object at the same time
                do{
                    BreakableObject* tmp = getCollidingObject(player);
                    if(playerSpeed.x > 0){
                        player->setPosition(tmp->getPosition().x - player->getHitbox().getGlobalBounds().width, player->getPosition().y);
                    }
                    else{
                        player->setPosition(tmp->getPosition().x + tmp->getHitbox().getGlobalBounds().width, player->getPosition().y);
                    }

                }while(playerIsColliding(player));
            }
        }

        if(playerSpeed.y != 0){
            player->move(Vector2f(0, playerSpeed.y), elapsedTime);

            //Check if the player isn't leaving the screen
            if(player->getPosition().y + player->getHitbox().getGlobalBounds().height > windowSize.y)
                player->setPosition(player->getPosition().x, windowSize.y - player->getHitbox().getGlobalBounds().height);
            else if(player->getPosition().y < skyHeight - player->getHitbox().getGlobalBounds().height/2)
                player->setPosition(player->getPosition().x, skyHeight - player->getHitbox().getGlobalBounds().height/2);

            if(bridge->detectHit(player)){
                if(playerSpeed.y > 0)
                    player->setPosition(player->getPosition().x, bridge->getSpriteBounds().top + bridge->getSpriteBounds().height - player->getHitbox().getGlobalBounds().height);
                else
                    player->setPosition(player->getPosition().x, bridge->getSpriteBounds().top - player->getHitbox().getGlobalBounds().height + Entity::DEPTH_DIFF);
            }



            if(playerIsColliding(player)){
                //Do/While in case the player collide several object at the same time
                do{
                    BreakableObject* tmp = getCollidingObject(player);
                    if(tmp->getHitbox().getGlobalBounds().height < Entity::DEPTH_DIFF){
                        if(playerSpeed.y > 0){
                            player->setPosition(player->getPosition().x, tmp->getPosition().y - player->getHitbox().getGlobalBounds().height);
                        }
                        else{
                            player->setPosition(player->getPosition().x, tmp->getPosition().y + tmp->getHitbox().getGlobalBounds().height -player->getHitbox().getGlobalBounds().height + Entity::DEPTH_DIFF);
                        }
                    }
                    else{
                        if(playerSpeed.y > 0){
                        player->setPosition(player->getPosition().x, tmp->getPosition().y + tmp->getHitbox().getGlobalBounds().height - player->getHitbox().getGlobalBounds().height - Entity::DEPTH_DIFF);
                        }
                        else{
                            player->setPosition(player->getPosition().x, tmp->getPosition().y + tmp->getHitbox().getGlobalBounds().height - player->getHitbox().getGlobalBounds().height + Entity::DEPTH_DIFF);
                        }
                    }


                }while(playerIsColliding(player));
            }

        }
    }
 }
*/

 //Move to Render class
 void Game::drawWithDepth(RenderWindow* app){

    list<Entity*> entities;

    for(BonusHp* var : bonuses_hp)
        entities.push_back((Entity*)var);

    for(ItemWeapon* var : item_weapons)
        entities.push_back((Entity*)var);

    /*for(Enemy* var : enemies){
        entities.push_back((Entity*)var);
        if(var->getEnemyType() == Enemy_Dragon)
            for(Flame* flame : ((Dragon*)var)->getFlames())
                entities.push_back((Entity*)flame);
    }*/
    for(Player* var : players)
        entities.push_back((Entity*)var);

    for(BreakableObject* var : breakable_objects)
        entities.push_back((Entity*)var);

    for(Player* player : players)
        for(Arrow* arrow : player->getArrows())
            entities.push_back((Entity*)arrow);

    entities.sort(cmp);

    for(Entity* var : entities)
        app->draw(*var);
	
	for (auto e : World::getEntities())
		app->draw(*e);
 }

 bool Game::cmp(Entity* a, Entity* d) {
    if(a->getDrawDepth() >= d->getDrawDepth())
        return false;
    return true;
}

void Game::dropItem(Bonus* drop, Vector2f dropPosition) {
	switch (drop->getBonusType()) {
		case Item_Onigiri:
			bonuses_hp.push_back(new BonusHp(BonusHp::ONIGIRI, dropPosition));
			break;
		case Item_Axe:
			item_weapons.push_back(new ItemWeapon(Axe, dropPosition));
			break;
		case Item_Bow:
			item_weapons.push_back(new ItemWeapon(Bow, dropPosition));
			break;
		case Item_Greatsword:
			item_weapons.push_back(new ItemWeapon(GreatSword, dropPosition));
			break;
		case Item_Sword:
			item_weapons.push_back(new ItemWeapon(Sword, dropPosition));
			break;
		default:
			break;
	}
}

//Function calls for levelManager
void Game::addEnemyInstance(Enemy* enemy) {
	World::addEntity(enemy);
}

void Game::addPlayerInstance(Player* player) {
	//this->players.push_back(player);
	World::addEntity(player, true);
}

