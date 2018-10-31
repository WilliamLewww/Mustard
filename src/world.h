#pragma once
#include "core\configuration.h"
#include "core\drawing.h"
#include "environment\environment.h"
#include "track.h"

class World {
private:	
	int mountainColor[3] = { 118, 92, 67 };
	int mountainOutlineColor[3] = { 78, 52, 27 };

	std::vector<Vector2> mountainPolygonsStart;
	std::vector<std::vector<Vector2>> mountainPolygons;
	std::vector<int> mountainOffsetValue;

	void drawMountainOutline();

	void generateSpeedZones();
	void generateTrack();

	void randomSpeedZone(int difficulty, int initialSpeed, int initialNode, int spacing);
	void randomGradualSpeedZone(int difficulty, int min, int max, int initialSpeed, int initialNode, int spacing);

	void givenInputFunction(int period, int buffer, double distance, double a, double b, Vector2 expandVal);
	void randomInputFunction(int functionCount, int period, int buffer, double distance, Vector2 betweenA, Vector2 betweenB, Vector2 expandVal);

	void randomLongTrackPar(int difficulty, int count, int points, int pointSpacing);
	void randomUpPar(int difficulty, int points, int pointSpacing);
	void randomDownPar(int difficulty, int points, int pointSpacing);
	void randomPar(int difficulty, int points, int pointSpacing);
public:
	Environment environment;
	Track track;
	
	void generateWorld();
	void update();
	void draw();
	void drawStatic();
	void drawStaticBackground();
	void reset();
	void generateMountainPolygons();
};