#ifndef TEXTURES_HPP_INCLUDED
#define TEXTURES_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

// Loads an image the first time it's asked for, then returns the same
// texture every time after that. The texture lives until the game exits.
const sf::Texture &getTexture(const std::string &path);

#endif
