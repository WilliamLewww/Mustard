#include "main.h"

Engine engine;

int main(int argc, char *argv[]) {
	engine.initialize();
	engine.start();
	engine.quit();

	return 0;
}

void Engine::initialize() {
	setScreenWidth(1000);
	setScreenHeight(600);

	displayWindow = SDL_CreateWindow("Thane", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-screenWidth / 2, screenWidth / 2, screenHeight / 2, -screenHeight / 2, 0, 1);

	initializeExternalController();
}

void Engine::initializeExternalController() {
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	input.setupController();	
}

void Engine::start() {
	while (isRunning) {
		handleEvents();
		delayEarlyFrames();
		updateAndRender();
	}
}

void Engine::quit() {
	SDL_Quit();
}

void Engine::handleEvents() {
	input.clearExpiredInput();

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		handleUserInput();
	}
}

void Engine::handleUserInput() {
	input.getKeyTrigger(event);
	input.getMouseTrigger(event);
}

void Engine::delayEarlyFrames() {
	if (deltaTime < 1 / 60) {
		frameStart = SDL_GetTicks();
		SDL_Delay(1);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}
}

void Engine::updateAndRender() {
	frameStart = SDL_GetTicks();
	update();
	render();
	frameEnd = SDL_GetTicks();
	deltaTime = frameEnd - frameStart; 
}

void Engine::handleEscapeKey() {
	if (std::find(input.getKeyList().begin(), input.getKeyList().end(), SDLK_ESCAPE) != input.getKeyList().end()) {
		isRunning = false;
	}
}

void Engine::update() {
	handleEscapeKey();
}

void Engine::render() {
	SDL_GL_MakeCurrent(displayWindow, context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glPopMatrix();

	SDL_GL_SwapWindow(displayWindow);
}