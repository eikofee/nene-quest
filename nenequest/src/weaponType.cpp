#include "../headers/weaponType.hpp"
#include "../headers/config.hpp"
#include <SFML/Graphics.hpp>

sf::Vector2f getWeaponOrigin(WeaponType w) {
    switch (w) {
        case Bow:
            break;
        case Axe:
            return sf::Vector2f(90,190);
        case Sword:
            return sf::Vector2f(100,270);
        case GreatSword:
            return sf::Vector2f(100,260);
    }
    return sf::Vector2f(1,1);
}

std::string getWeaponPath(WeaponType w) {

    switch (w) {
        case Bow:
            return GSP_WEAPON_BOW;
        case Axe:
            return GSP_WEAPON_AXE;
        case Sword:
            return GSP_WEAPON_SWORD;
        case GreatSword:
            return GSP_WEAPON_GREATSWORD;
        default:
            return "";
    }
}

int getWeaponDamage(WeaponType w)
{
     switch (w) {
        case Bow:
            return 1;
        case Axe:
            return 3;
        case Sword:
            return 1;
        case GreatSword:
            return 2;
		default:
			return 0;
    }
}
