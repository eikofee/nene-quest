#include "weaponType.hpp"

#include <SFML/Graphics.hpp>

sf::Vector2f getWeaponOrigin(WeaponType w) {
    switch (w) {
        case Bow:
            return sf::Vector2f(0, 280);
        case Axe:
            return sf::Vector2f(0, 190);
        case Sword:
            return sf::Vector2f(0, 270);
        case GreatSword:
            return sf::Vector2f(0, 260);
    }
    return sf::Vector2f(0, 0);
}

sf::Vector2f getWeaponOffset(WeaponType w) {
    switch (w) {
        case Bow:
            return sf::Vector2f(-130, 0);
        case Axe:
            return sf::Vector2f(-90, 0);
        case Sword:
            return sf::Vector2f(-100, 0);
        case GreatSword:
            return sf::Vector2f(-100, 0);  // todo
    }
    return sf::Vector2f(0, 0);
}

std::string getWeaponPath(WeaponType w) {
    switch (w) {
        case Bow:
            return "img/weapon_bow.png";
        case Axe:
            return "img/weapon_axe.png";
        case Sword:
            return "img/weapon_sword.png";
        case GreatSword:
            return "img/weapon_sword2.png";
        default:
            return "";
    }
}

int getWeaponDamage(WeaponType w) {
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

WeaponType parse(std::string s) {
    if (s == "Bow") return Bow;
    if (s == "Axe") return Axe;
    if (s == "Sword") return Sword;
    if (s == "GreatSword") return GreatSword;

    // TODO: Add proper invalid value
    return Sword;
}
