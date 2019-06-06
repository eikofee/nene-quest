#ifndef CONFIGPARAMETER_H
#define CONFIGPARAMETER_H

#include <SFML/Window.hpp>
#include <string>

class ConfigParameter {
   public:
    void getParameter(sf::Keyboard::Key *k);
    void getParameter(int *i);
    void getParameter(std::string *s);
    ConfigParameter(sf::Keyboard::Key key);
    ConfigParameter(int i);
    ConfigParameter(std::string str);

   private:
    sf::Keyboard::Key key;
    int i;
    std::string str;
};

#endif
