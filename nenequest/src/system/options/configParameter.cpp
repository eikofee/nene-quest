#include "configParameter.hpp"

void ConfigParameter::getParameter(sf::Keyboard::Key *k) { *k = key; }

void ConfigParameter::getParameter(int *i) { *i = this->i; }

void ConfigParameter::getParameter(std::string *s) { *s = str; }

ConfigParameter::ConfigParameter(sf::Keyboard::Key key) { this->key = key; }

ConfigParameter::ConfigParameter(int i) { this->i = i; }

ConfigParameter::ConfigParameter(std::string str) { this->str = str; }
