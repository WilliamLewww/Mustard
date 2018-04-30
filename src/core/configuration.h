#pragma once
#include <map>
#include <fstream>

class Configuration {
private:
	int screenWidth, screenHeight;
	std::map<std::string, int> configurations;

	void grabConfigurationFromFile();
	void linkScreenSize();
public:
	inline std::map<std::string, int> getConfigurations() { return configurations; };
	inline void setConfiguration(std::string name, int value) { configurations[name] = value; };

	inline int getScreenWidth() { return screenWidth; };
	inline int getScreenHeight() { return screenHeight; };

	void initialize();
};

extern Configuration configuration;