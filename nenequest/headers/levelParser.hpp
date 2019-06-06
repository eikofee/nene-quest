#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "levelManager.hpp"

class ParserFunction;
class ParserCommand;

class LevelParser {
   private:
    std::vector<ParserFunction *> functions;
    LevelManager *manager;
    std::string levelFilePath;
    std::vector<ParserCommand *> commands;

   public:
    LevelParser();
    void initialize();
    void parseFile(std::string filename);
    void setLevelFilesPath(std::string path);
    void setLevelManager(LevelManager *manager);
    void addFunction(ParserFunction *function);
};

#endif
