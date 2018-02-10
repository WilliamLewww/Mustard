#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include "src\input.h"

class Engine {
private:
	Input input;

	SDL_Event event;
	SDL_GLContext context;
	SDL_Window* displayWindow;

	int screenWidth, screenHeight;

	bool isRunning = true; 
	int frameStart, frameEnd, deltaTime = 0;

public:
	inline void setScreenWidth(int screenWidth) { this->screenWidth = screenWidth; }
	inline void setScreenHeight(int screenHeight) { this->screenHeight = screenHeight; }
	inline int getScreenWidth() { return screenWidth; }
	inline int getScreenHeight() { return screenHeight; }

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
};

extern Engine engine;