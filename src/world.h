#pragma once
#include "core\drawing.h"
#include "track.h"

class World {
private:
	int mountainColor[3] = { 118, 92, 67 };

	std::vector<std::vector<Vector2>> mountainPolygons;
	std::vector<int> mountainOffsetValue;

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
	Track track;
	
	void generateWorld();
	void draw();

	void reset();

	void generateMountainPolygons();
};