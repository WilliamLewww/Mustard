#pragma once
#include <map>
#include <fstream>
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include "src\input.h"
#include "src\joiner.h"

class Engine {
private:
	Input input;
	Joiner joiner;

	SDL_Event event;
	SDL_GLContext displayContext;
	SDL_Window* displayWindow;

	int screenWidth, screenHeight;

	bool isRunning = true; 
	int frameStart, frameEnd, deltaTime = 0;

	std::map<std::string, int> configurationsFromFile;

public:
	inline void setScreenWidth(int screenWidth) { this->screenWidth = screenWidth; };
	inline void setScreenHeight(int screenHeight) { this->screenHeight = screenHeight; };
	inline int getScreenWidth() { return screenWidth; };
	inline int getScreenHeight() { return screenHeight; };
	inline std::map<std::string, int> getConfigurationFromFile() { return configurationsFromFile; };

	void initialize();
	void initializeExternalController();
	void start();
	void quit();
	void handleEvents();
	void handleUserInput();
	void handleEscapeKey();
	void delayEarlyFrames();
	void updateAndRender();
	void update();
	void render();
	void grabConfiguration();
};

extern Engine engine;