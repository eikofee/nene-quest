#ifndef WEAPONTYPE_HPP_INCLUDED
#define WEAPONTYPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

enum WeaponType {Bow, Axe, Sword, GreatSword};

sf::Vector2f getWeaponOrigin(WeaponType w);

sf::Vector2f getWeaponOffset(WeaponType w);

std::string getWeaponPath(WeaponType w);

int getWeaponDamage(WeaponType w);

WeaponType parse(std::string s);

#endif
