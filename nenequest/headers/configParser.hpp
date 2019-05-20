#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <SFML/Window.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ConfigManager;
class ConfigParser {
   private:
    ConfigManager *manager;
    std::string configFilesPath;
    std::vector<std::string> paramsKeyboardType;
    std::vector<std::string> paramsIntType;
    std::vector<std::string> paramsStringType;

    // Helpers
    std::vector<std::string> configKeyboardNames;
    std::vector<sf::Keyboard::Key> configKeyboardEquiv;
    sf::Keyboard::Key parseKey(std::string str);
    bool isIn(std::string value, std::vector<std::string> vec);

   public:
    ConfigParser();
    void initialize();
    void parseFile(std::string filename);
    void setConfigFilesPath(std::string path);
    void setConfigManager(ConfigManager *manager);
};

#endif