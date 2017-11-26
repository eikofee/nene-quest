#include<configProperty.h>

ConfigProperty::ConfigProperty(std::string name, ConfigParameter * param)
{
	this->name = name;
	this->param = param;
}

std::string ConfigProperty::getName()
{
	return this->name;
}

ConfigParameter * ConfigProperty::getParameter()
{
	return this->param;
}

void ConfigProperty::setParameter(ConfigParameter* param) {
	this->param = param;
}
