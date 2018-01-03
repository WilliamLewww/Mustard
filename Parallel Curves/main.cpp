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

/* NOTEPAD

Example Equation
y = sin(x)
f(t) = x
g(t) = y

parametric equations
x = (distance * g'(t)) / sqrt(pow(f'(t), 2) + pow(g'(t), 2)) + f(t);
y = -(distance * f'(t)) / sqrt(pow(f'(t), 2) + pow(g'(t), 2)) + g(t);
(x, y)

Original Equation = 5 * sin(0.5 * x)
g(t) = 5 * sin(0.5 * x)
f(t) = x
g'(t) = (5 * cos(0.5 * x)) / 2 
f'(t) = 0.5

*/

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

double distance = 0.5; // between 0 and 1.5

double a = 1, // between -1 and 1
	   b = 2; // between  0 and 2

double f(double x) { return (a * sin(b * x)); }
double fDerivative(double x) { return (a * b * cos(b * x)); }
double g(double x) { return x; }
double gDerivative(double x) { return b; }

void initialize() {
	track.addRail(2);

	for (double x = 0; x < 10; x += 0.1) {
		track.addVertexSingle(0, Vector2(x, f(x)));
		track.addVertexSingle(1, Vector2(
			(distance * fDerivative(x)) / sqrt(pow(gDerivative(x), 2) + pow(fDerivative(x), 2)) + g(x),
			-(distance * gDerivative(x)) / sqrt(pow(gDerivative(x), 2) + pow(fDerivative(x), 2)) + f(x)));
	}

	for (Vector2& vector : track.railList[0]) { vector.expand(50, 50); }
	for (Vector2& vector : track.railList[1]) { vector.expand(50, 50); }
}

void update(int elapsedTime) {
	if (std::find(keyList.begin(), keyList.end(), SDLK_w) != keyList.end()) { cameraPosition.y -= 5.0; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_s) != keyList.end()) { cameraPosition.y += 5.0; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) { cameraPosition.x -= 5.0; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) { cameraPosition.x += 5.0; }
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