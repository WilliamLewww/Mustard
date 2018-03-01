#pragma once
#include <ctime>
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include "src\configuration.h"
#include "src\drawing.h"
#include "src\input.h"
#include "src\joiner.h"

class Engine {
private:
	SDL_Event event;
	SDL_GLContext displayContext;
	SDL_Window* displayWindow;

	bool isRunning = true; 
	int frameStart, frameEnd, deltaTime = 0;

	void initializeExternalController();
	void enableBlendAlpha();
	void seedRandom();
	void handleEvents();
	void handleUserInput();
	void delayEarlyFrames();
	void updateAndRender();
	void update();
	void handleEscapeKey();
	void render();
public:
	inline Drawing getDrawing() { return drawing; };

	void initialize();
	void start();
	void quit();
};