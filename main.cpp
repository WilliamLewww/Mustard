#include "main.h"
#include <fstream>

void initialize();
void update(int elapsedTime);
void render(SDL_Window* window, SDL_GLContext context);

void grabConfig();

int generationStyle = -1;
int SCREENWIDTH = 1920, SCREENHEIGHT = 1080;

Joiner joiner;

SDL_Event event;
SDL_GLContext context;

bool isRunning = true; 
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	grabConfig();

	displayWindow = SDL_CreateWindow("Hotdog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	initialize();

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
	
	SDL_Quit();

	return 0;
}

void initialize() {
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	getController();

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	srand(time(NULL));
	joiner.initialize(generationStyle);
}

void update(int elapsedTime) {
	if (std::find(keyList.begin(), keyList.end(), SDLK_ESCAPE) != keyList.end()) {
		isRunning = false;
	}
	
	joiner.update(elapsedTime);
}

void render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(convertColor(28), convertColor(107), convertColor(160), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	joiner.draw();
	glPopMatrix();

	SDL_GL_SwapWindow(window);
}

int readStep = 0;
void grabConfig() {
	std::ifstream fin("config.txt");

	int x;
	while (fin >> x) {
		switch (readStep) {
			case 0:
				if (x > 1920) { SCREENWIDTH = 1920; }
				else { SCREENWIDTH = x; }
				readStep += 1;
				break;
			case 1:
				if (x > 1080) { SCREENHEIGHT = 1080; }
				else { SCREENHEIGHT = x; }
				readStep += 1;
				break;
			case 2:
				generationStyle = x;
				readStep += 1;
				break;
		}
	}

	fin.close();
}