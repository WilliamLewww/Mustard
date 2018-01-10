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

Process
	1.flatten start
	2.generate curve from function
	3.flatten end
	4.repeat steps 1-3
-
*/

Track track;
Vector2 cameraPosition = Vector2(0,0);

//double distance = -0.5; // between -0.5 and 0

//double a = 1, // between -1 and 1
//	     b = 2; // between  0 and 2

double f(double x, double a, double b) { return (a * sin(b * x)); }
double fDerivative(double x, double a, double b) { return (a * b * cos(b * x)); }
double g(double x, double a, double b) { return x; }
double gDerivative(double x, double a, double b) { return b; }

void givenInputFunction(Track& track, int period, int buffer, double distance, double a, double b, Vector2 expandVal) {
	std::vector<Vector2> railA;
	std::vector<Vector2> railB;

	for (double x = 0; x < period; x += 0.1) {
		railA.push_back(Vector2(x, f(x, a, b)));
		railB.push_back(Vector2(
			(distance * fDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + g(x, a, b),
			-(distance * gDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + f(x, a, b)));
	}

	Vector2 initialPoint = track.railList[0][track.railList[0].size() - 1];
	for (Vector2& vector2 : railA) { 
		vector2.expand(expandVal.x, expandVal.y);
		track.addVertexSingle(0, vector2 + initialPoint + Vector2(buffer, 0));
	}
	for (Vector2& vector2 : railB) { 
		vector2.expand(expandVal.x, expandVal.y); 
		track.addVertexSingle(1, vector2 + initialPoint + Vector2(buffer, 0));
	}
}

void randomInputFunction(Track& track, int functionCount, int period, int buffer, double distance, Vector2 betweenA, Vector2 betweenB, Vector2 expandVal) {
	std::vector<Vector2> railA;
	std::vector<Vector2> railB;

	for (int count = 0; count < functionCount; count++) {
		double a = (rand() % (int)(betweenA.y - betweenA.x + 1) + betweenA.x) / 10;
		double b = (rand() % (int)(betweenB.y - betweenB.x + 1) + betweenB.x) / 10;

		for (double x = 0; x < period; x += 0.1) {
			railA.push_back(Vector2(x, f(x, a, b)));
			railB.push_back(Vector2(
				(distance * fDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + g(x, a, b),
				-(distance * gDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + f(x, a, b)));
		}

		Vector2 initialPoint = track.railList[0][track.railList[0].size() - 1];
		for (Vector2& vector2 : railA) { 
			vector2.expand(expandVal.x, expandVal.y);
			track.addVertexSingle(0, vector2 + initialPoint + Vector2(buffer, 0));
		}
		for (Vector2& vector2 : railB) { 
			vector2.expand(expandVal.x, expandVal.y); 
			track.addVertexSingle(1, vector2 + initialPoint + Vector2(buffer, 0));
		}

		railA.clear();
		railB.clear();
	}
}

void initialize() {
	srand(time(NULL));
	track.addRail(2);

	track.addVertex(0, 1, Vector2(SCREENWIDTH / 2 - 10, SCREENHEIGHT / 2 - 20), 0);
	track.addVertex(0, 1, Vector2(SCREENWIDTH / 2 - 10, SCREENHEIGHT / 2 - 20), 45);
	track.addVertexRelative(0, 1, -25, 100, 25);
	track.addVertexRelative(0, 1, 0, 150, 0);
	//givenInputFunction(track, 10, 100, -0.3, 1, 2, Vector2(250, 250));
	randomInputFunction(track, 25, 5, 50, -0.3, Vector2(-10, 10), Vector2(0, 20), Vector2(50, 50));
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