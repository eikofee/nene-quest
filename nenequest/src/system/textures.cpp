#include "textures.hpp"

#include <map>

const sf::Texture &getTexture(const std::string &path) {
    // Never deleted on purpose: destroying textures at exit, after the
    // window and its OpenGL context are gone, can crash
    static auto *textures = new std::map<std::string, sf::Texture>();

    auto found = textures->find(path);
    if (found != textures->end()) return found->second;

    // std::map never moves its elements, so the reference stays valid
    sf::Texture &texture = (*textures)[path];
    texture.loadFromFile(path);
    return texture;
}
