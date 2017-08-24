#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include "../headers/parserFunction.hpp"
#include "../headers/levelManager.hpp"
#include "../headers/parserCommand.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
class LevelParser {

	private:
		std::vector<ParserFunction*> functions;
		LevelManager* manager;
		std::string levelFilePath;
		std::vector<ParserCommand*> commands;

	public:
		LevelParser();
		void parseFile(std::string filename);
		void setLevelFilesPath(std::string path);
		void setLevelManager(LevelManager* manager);
		void addFunction(ParserFunction* function);
};

#endif