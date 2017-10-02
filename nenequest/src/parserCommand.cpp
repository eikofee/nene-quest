#include "../headers/parserCommand.hpp"

ParserCommand::ParserCommand() {
}

void ParserCommand::setTime(float time){
	this->time = time;
}

void ParserCommand::setName(std::string name) {
	this->name = name;
}

void ParserCommand::setFunction(ParserFunction* function) {
	this->function = function;
}

void ParserCommand::addArgument(std::string key, std::string value) {
	this->arguments.insert({ key, value });
}

float ParserCommand::getTime() {
	return this->time;
}

std::string ParserCommand::getName() {
	return this->name;
}

ParserFunction* ParserCommand::getFunction() {
	return this->function;
}

std::map<std::string, std::string>* ParserCommand::getArguments() {
	return &this->arguments;
}
