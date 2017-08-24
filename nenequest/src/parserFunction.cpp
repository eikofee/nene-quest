#include "..\headers\parserFunction.hpp"

ParserFunction::ParserFunction(){

}

bool ParserFunction::isCorrect(std::string command) {
	for (auto k : this->commands)
		if (!k.compare(command))
			return true;

	return false;
}