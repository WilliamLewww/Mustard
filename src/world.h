#pragma once
#include "core\configuration.h"
#include "core\drawing.h"
#include "environment\environment.h"
#include "track.h"

class World {
private:
	SDL_Color tutorialColor1 = { 30, 87, 100 };
	SDL_Color tutorialColor2 = { 115, 55, 80 };
	SDL_Color tutorialColor3 = { 76, 59, 42 };

	int mountainColor[3] = { 118, 92, 67 };
	int mountainOutlineColor[3] = { 78, 52, 27 };

	std::vector<Vector2> mountainPolygonsStart;
	std::vector<std::vector<Vector2>> mountainPolygons;
	std::vector<int> mountainOffsetValue;

	void drawMountainOutline();

	void generateSpeedZones();
	void generateTrack(int tutorialState);

	void randomSpeedZone(int difficulty, int initialSpeed, int initialNode, int spacing);
	void randomGradualSpeedZone(int difficulty, int min, int max, int initialSpeed, int initialNode, int spacing);

	void givenInputFunction(int period, int buffer, double distance, double a, double b, Vector2 expandVal);
	void randomInputFunction(int functionCount, int period, int buffer, double distance, Vector2 betweenA, Vector2 betweenB, Vector2 expandVal);

	void randomLongTrackPar(int difficulty, int count, int points, int pointSpacing);
	void randomUpPar(int difficulty, int points, int pointSpacing);
	void randomDownPar(int difficulty, int points, int pointSpacing);
	void randomPar(int difficulty, int points, int pointSpacing);

	int tutorialEnd = 0, endNode = 0;
	void generateTutorial(int state);
	void drawTutorial(int state);
public:
	Environment environment;
	Track track;
	
	int generateWorld(int tutorialState);
	void update();
	void draw(int tutorialState);
	void drawStatic();
	void drawStaticBackground();
	void reset();
	void generateMountainPolygons();
};