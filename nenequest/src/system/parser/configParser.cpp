#include "configParser.hpp"
#include "configManager.hpp"
#include <SFML/Window.hpp>

ConfigParser::ConfigParser()
{
	configFilesPath = "config";
}

void ConfigParser::initialize()
{
	paramsKeyboardType = {
		"playerOneMoveUp" , "playerOneMoveDown", "playerOneMoveLeft",
		"playerOneMoveRight", "playerOneJump", "playerOneAttack",

		"playerTwoMoveUp" , "playerTwoMoveDown", "playerTwoMoveLeft",
		"playerTwoMoveRight", "playerTwoJump", "playerTwoAttack",

		"togglePause", "toggleDebugMode"
	};

	paramsIntType = {
		"fullscreen", "resolution"
	};

	paramsStringType = {

	};


	//Helpers
	configKeyboardNames = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"UP", "DOWN", "LEFT", "RIGHT", "SPACE", "RETURN", "LSHIFT", "LCTRL", "LALT",
		"NP0", "NP1", "NP2", "NP3", "NP4", "NP5", "NP6", "NP7", "NP8", "NP9",
	};

	configKeyboardEquiv = { sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::C, sf::Keyboard::D, sf::Keyboard::E, sf::Keyboard::F, sf::Keyboard::G, sf::Keyboard::H, sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L, sf::Keyboard::M, sf::Keyboard::N, sf::Keyboard::O, sf::Keyboard::P, sf::Keyboard::Q, sf::Keyboard::R, sf::Keyboard::S, sf::Keyboard::T, sf::Keyboard::U, sf::Keyboard::V, sf::Keyboard::W, sf::Keyboard::X, sf::Keyboard::Y, sf::Keyboard::Z,
		sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Space, sf::Keyboard::Return, sf::Keyboard::LShift, sf::Keyboard::LAlt, sf::Keyboard::LControl,
		sf::Keyboard::Numpad0, sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, sf::Keyboard::Numpad3, sf::Keyboard::Numpad4, sf::Keyboard::Numpad5, sf::Keyboard::Numpad6, sf::Keyboard::Numpad7, sf::Keyboard::Numpad8, sf::Keyboard::Numpad9,
	};
}

void ConfigParser::parseFile(std::string filename)
{
	std::string line;
	std::ifstream file(this->configFilesPath + "/" + filename);
	if (file.is_open()) {
		while (std::getline(file, line)) {
			if (line.length() > 1 && line.at(0) != ';')
			{
				//get parameter name
				std::string ds = "=";
				std::string name = line.substr(0, line.find(ds));

				//get parameter value		//TO CHECK/FIX
				std::string v = line.substr(line.find(ds) + 1, line.length() - 1);

				if (isIn(name, paramsKeyboardType)) {
					sf::Keyboard::Key k = parseKey(v);
					manager->setParameter(name, k);
				}else if (isIn(name, paramsIntType)) {
					int i = std::stoi(v);
					manager->setParameter(name, i);
				}else if (isIn(name, paramsStringType)) {
					manager->setParameter(name, v);
				}
			}

		}
	}
}

void ConfigParser::setConfigFilesPath(std::string path)
{
	configFilesPath = path;
}

void ConfigParser::setConfigManager(ConfigManager * manager)
{
	this->manager = manager;
}

sf::Keyboard::Key ConfigParser::parseKey(std::string str) {
	for (decltype(configKeyboardNames)::size_type i = 0;
		i < configKeyboardNames.size(); ++i)
		if (str == configKeyboardNames[i])
			return configKeyboardEquiv[i];

	return sf::Keyboard::Key::Unknown;
}

bool ConfigParser::isIn(std::string value, std::vector<std::string> vec) {
	for (auto v : vec) {
		if (!value.compare(v))
			return true;
	}

	return false;
}
