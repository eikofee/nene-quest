#include "parserFunction.hpp"

ParserFunction::ParserFunction() {}

void ParserFunction::initialize(LevelManager *manager) {}

bool ParserFunction::isCorrect(std::string command) {
    for (auto k : this->commands)
        if (!k.compare(command)) return true;

    return false;
}

void ParserFunction::exec(CustomMap *args) {}
