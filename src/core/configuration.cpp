#include "configuration.h"

Configuration configuration;

void Configuration::initialize() {
	grabConfigurationFromFile();
	setScreenSize();
}

void Configuration::grabConfigurationFromFile() {
	std::ifstream configFile("config.txt");
	std::string lineFromFile;
	while (std::getline(configFile, lineFromFile)) {
		if (lineFromFile[0] != '#') {
			configurations[lineFromFile.substr(0, lineFromFile.find(" "))] 
				= atoi(lineFromFile.substr(lineFromFile.find(" ") + 1, lineFromFile.length()).c_str());
		}
	}
}

void Configuration::setScreenSize() {
	screenWidth = getConfigurations()["ScreenWidth"];
	screenHeight = getConfigurations()["ScreenHeight"];
}