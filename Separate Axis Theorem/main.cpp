#include "main.h"

void initialize();
void update(int elapsedTime);
void render(SDL_Window* window, SDL_GLContext context);

SDL_Event event;
SDL_GLContext context;

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Separate Axis Theorem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);
	initialize();

	SDL_Init(SDL_INIT_GAMECONTROLLER);
	getController();

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

VRectangle objectA;
int color[3];
void initialize() {
	objectA = VRectangle(Vector2(250, 250), 50.0, 50.0, 0.0);
	color[0] = 255;
	color[1] = 0;
	color[2] = 0;
}

void update(int elapsedTime) {
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end()) {
		objectA.angle += 0.1;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end()) {
		objectA.angle -= 0.1;
	}
}

void render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	drawRect(objectA);

	SDL_GL_SwapWindow(window);
}