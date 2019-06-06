#include "configManager.hpp"
#include "configParameter.hpp"
#include "configProperty.hpp"
ConfigManager::ConfigManager() {}

ConfigParameter *ConfigManager::getParameter(std::string name) {
    ConfigParameter *res = NULL;
    for (auto p : properties) {
        if (!p->getName().compare(name)) res = p->getParameter();
    }

    return res;
}

void ConfigManager::setParameter(std::string name, ConfigParameter *param) {
    bool isNew = true;
    for (auto p : properties) {
        if (!p->getName().compare(name)) {
            isNew = false;
            p->setParameter(param);
        }
    }

    if (isNew) properties.push_back(new ConfigProperty(name, param));
}

void ConfigManager::setParameter(std::string name, sf::Keyboard::Key key) {
    setParameter(name, new ConfigParameter(key));
}

void ConfigManager::setParameter(std::string name, int i) {
    setParameter(name, new ConfigParameter(i));
}

void ConfigManager::setParameter(std::string name, std::string str) {
    setParameter(name, new ConfigParameter(str));
}
