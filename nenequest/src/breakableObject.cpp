#include "../headers/breakableObject.hpp"
#include"../headers/itemWeapon.hpp"
#include"../headers/bonusHp.hpp"


using namespace sf;

BreakableObject::BreakableObject(ObjectType o, Vector2f position) {

    object_type = o;

    getObjectTexture(o);

	sprite.setTexture(texture);
    sprite.setPosition(position);

    updateHitboxSize();
    updateHitboxPosition();

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
    int num = rand()% Number_of_Bonuses;
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

    if(object_type == Chest)
        return bonus;

    else if(object_type == Barrel){
        if(rand() % 10 > 6)
            return bonus;
        else
            return NULL;
    }


}
