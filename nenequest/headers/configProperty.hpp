#ifndef CONFIGPROPERTY_H
#define CONFIGPROPERTY_H
#include <string>

class ConfigParameter;

class ConfigProperty {
   public:
    ConfigProperty(std::string name, ConfigParameter *param);
    std::string getName();
    ConfigParameter *getParameter();
    void setParameter(ConfigParameter *param);

   private:
    std::string name;
    ConfigParameter *param;
};

#endif  // !CONFIGPROPERTY_H
