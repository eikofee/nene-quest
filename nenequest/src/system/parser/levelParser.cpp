#include <levelParser.hpp>

#include <commands/cmdScroll.h>
#include <commands/cmdBridge.h>
#include <commands/cmdChest.h>
#include <commands/cmdStart.h>
#include <parserCommand.hpp>

LevelParser::LevelParser() {

}

void LevelParser::initialize()
{
	this->addFunction(new cmdScroll());
	this->addFunction(new cmdStart());
	this->addFunction(new cmdChest());
	this->addFunction(new cmdBridge());

	for (auto f : this->functions)
		f->initialize(this->manager);
}

void LevelParser::parseFile(std::string filename) {
	std::string line;
	std::ifstream file (this->levelFilePath + "/" + filename);
	if (file.is_open()) {
		while (std::getline(file, line)) {
			//get time
			std::string ds = ":";
			float time = std::stof(line.substr(0, line.find(ds)));

			//get function + args
			std::string fa = line.substr(line.find(ds) + 1, line.length() - 1);

			ds = "[";
			std::string func_name = "";
			std::string func_args = "";
			std::vector<std::string> args_s;
			if (fa.find(ds) != std::string::npos)
			{

				func_name = fa.substr(0, fa.find(ds));
				func_args = fa.substr(fa.find(ds) + 1, fa.length() - 1);
				func_args = func_args.substr(0 , func_args.length() - 1);


				//C/C from SO because I have no shame
				size_t pos = 0;
				std::string token;
				ds = ",";
				while ((pos = func_args.find(ds)) != std::string::npos) {
					token = func_args.substr(0, pos);
					args_s.push_back(token);
					func_args.erase(0, pos + ds.length());
				}

				args_s.push_back(func_args);
			}
			else {
				func_name = fa;
			}

			ParserCommand* c = new ParserCommand();
			c->setTime(time);
			c->setName(func_name);
			for (auto a : args_s) {
				std::replace(a.begin(), a.end(), ' ', '\0');
				ds = "=";
				std::string k = a.substr(0, a.find(ds));
				std::string v = a.substr(a.find(ds) + 1, a.length() - 1);
				c->addArgument(k, v);
			}

			this->commands.push_back(c);
		}

		file.close();
	}

	for (auto c : this->commands) {
		ParserFunction* f = this->functions.at(0);
		int i = 0;
		while (i < this->functions.size() && !f->isCorrect(c->getName()))
			f = this->functions.at(i++);

		c->setFunction(f);
	}

	manager->setLevelCommands(this->commands);

}

void LevelParser::setLevelFilesPath(std::string path) {
	this->levelFilePath = path;
}

void LevelParser::setLevelManager(LevelManager* manager) {
	this->manager = manager;
}

void LevelParser::addFunction(ParserFunction* function) {
	this->functions.push_back(function);
}