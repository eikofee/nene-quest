#include <bonus.hpp>

Bonus::Bonus() {
    //ctor
}

Bonus::~Bonus() {
    //dtor
}

BonusType Bonus::getBonusType(){
    return bonus_type;
}

EntityType Bonus::getEntityType() {
	return BONUS;
}
