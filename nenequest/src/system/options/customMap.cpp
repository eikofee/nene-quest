#include "customMap.hpp"

CustomMap::CustomMap(std::map<std::string, std::string> *map) {
    this->map = map;
}

std::string CustomMap::getOrDefault(std::string key, std::string def_value) {
    if (map->count(key))
        return map->at(key);
    else
        return def_value;
}
