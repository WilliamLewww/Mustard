#include "main.h"

void initialize();
void update(int elapsedTime);
void render(SDL_Window* window, SDL_GLContext context);

SDL_Event event;
SDL_GLContext context;

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Parallel Curves", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
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

// Example Equation
// y = sin(x)
// f(t) = x
// g(t) = y

//parametric equations
// x = (a * g'(t)) / sqrt(pow(f'(t), 2) + pow(g'(t), 2)) + f(t);
// y = -(a * f'(t)) / sqrt(pow(f'(t), 2) + pow(g'(t), 2)) + g(t);
// (x, y)

// Original Equation = 5 * sin(0.5 * x)
// g(t) = 5 * sin(0.5 * x)
// f(t) = x
// g'(t) = (5 * cos(0.5 * x)) / 2 
// f'(t) = 0.5

Track track;
Vector2 cameraPosition = Vector2(0,0);

double a = 0.5;
void initialize() {
	track.addRail(2);

	for (int x = 0; x < 1000; x++) {
		track.addVertexSingle(0, Vector2(x, 5 * sin(0.5 * x)));
		track.addVertexSingle(1, Vector2(
			(a * (5 * cos(0.5 * x)) / 2) / sqrt(pow(0.5, 2) + pow((5 * cos(0.5 * x)) / 2 , 2)) + x,
			-(a * 0.5) / sqrt(pow(0.5, 2) + pow((5 * cos(0.5 * x)) / 2 , 2)) + 5 * sin(0.5 * x)));
	}

	for (Vector2& vector : track.railList[0]) { vector.expand(300, 300); }
	for (Vector2& vector : track.railList[1]) { vector.expand(300, 300); }
}

void update(int elapsedTime) {
	if (std::find(keyList.begin(), keyList.end(), SDLK_w) != keyList.end()) { cameraPosition.y -= 2.5; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_s) != keyList.end()) { cameraPosition.y += 2.5; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) { cameraPosition.x -= 2.5; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) { cameraPosition.x += 2.5; }
}

void render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(-cameraPosition.x, -cameraPosition.y, 0);
	track.draw();
	glPopMatrix();

	SDL_GL_SwapWindow(window);
}