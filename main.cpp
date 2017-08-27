#include "main.h"

void update(int elapsedTime);
void render(SDL_Window* window, SDL_GLContext context);

Joiner joiner;

SDL_Event event;
SDL_GLContext context;

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Hotdog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	SDL_Init(SDL_INIT_GAMECONTROLLER);
	getController();

	srand(time(NULL));
	joiner.initialize();

	while (isRunning) {
		removeInitialPress();
		leftButtonPress = false;
		middleMousePress = false;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;

			getKeys(event);
			getButtons(event);
		}

		if (deltaTime < 1 / 60) {
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}
		frameStart = SDL_GetTicks();
		update(deltaTime);
		render(displayWindow, context);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}

	return 0;
}

void update(int elapsedTime) {
	joiner.update(elapsedTime);
}

void render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	joiner.draw();

	SDL_GL_SwapWindow(window);
}