#pragma once
#include "file.h"

class Configuration {
private:
	int screenWidth, screenHeight;
	std::map<std::string, int> configurations;

	void grabConfiguration();
	void linkScreenSize();
public:
	inline std::map<std::string, int> getConfigurations() { return configurations; };
	inline void setConfiguration(std::string name, int value) { configurations[name] = value; };

	inline int getScreenWidth() { return screenWidth; };
	inline int getScreenHeight() { return screenHeight; };

	void initialize();
};

extern Configuration configuration;