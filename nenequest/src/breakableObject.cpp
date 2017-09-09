#include "../headers/breakableObject.hpp"
#include"../headers/itemWeapon.hpp"
#include"../headers/bonusHp.hpp"


using namespace sf;

BreakableObject::BreakableObject(ObjectType o, Vector2f position, BonusType argDrop) {

    drop = argDrop;

    object_type = o;

    getObjectTexture(o);

	sprite.setTexture(texture);
    updateHitboxSize();

    hitbox.setPosition(position);
    updateSpritePosition();
}

BreakableObject::~BreakableObject() {
    //dtor
}

void BreakableObject::getObjectTexture(ObjectType o){

    if(o == Chest)
        texture.loadFromFile("img/obj_chest.png");
    else if(o == Barrel)
        texture.loadFromFile("img/obj_barrel.png");

}

Bonus* BreakableObject::getDrops(){

    Bonus* bonus;
    int num;

    if(drop == Item_Random){
        num = rand()% Number_of_Bonuses;
    }
    else if(drop == Item_None){
        return NULL;
    }
    else{
        num = drop;
    }


    if(num == Item_Axe){
        bonus = new ItemWeapon(Axe, this->getPosition());
    }
    else if(num == Item_Bow){
        bonus = new ItemWeapon(Bow, this->getPosition());
    }
    else if(num == Item_Greatsword){
        bonus = new ItemWeapon(GreatSword, this->getPosition());
    }
    else if(num == Item_Sword){
        bonus = new ItemWeapon(Sword, this->getPosition());
    }
    else if(num == Item_Onigiri){
        bonus = new BonusHp(BonusHp::ONIGIRI, this->getPosition());
    }

    //Randomize the chances of getting a drop of a barrel if the drop isn't set
    if(object_type == Barrel && drop == Item_Random){
        if(rand() % 10 < BARREL_DROP_CHANCE)
            return bonus;
        else
            return NULL;
    }
    else
        return bonus;
}
