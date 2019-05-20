#ifndef CONFIGPARAMETER_H
#define CONFIGPARAMETER_H

#include <string>
#include <SFML/Window.hpp>

class ConfigParameter {
public :
	void getParameter(sf::Keyboard::Key* k);
	void getParameter(int* i);
	void getParameter(std::string* s);
	ConfigParameter(sf::Keyboard::Key key);
	ConfigParameter(int i);
	ConfigParameter(std::string str);

private :
	sf::Keyboard::Key key;
	int i;
	std::string str;
};

#endif
