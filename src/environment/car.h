#pragma once
#include "..\core\vector2.h"
#include "..\bmp_polygon.h"

class Car {
private:
	BitmapPolygon polygon;

	Vector2 directionVector;
	float distanceToNode;

	Vector2 projectedPoint;

	Vector2 currentRail;
	int currentRailIndex;

	int spacing;

	int speed = 75, turnSpeed = 50;

	bool isLeft = false;
	int color[3] = { 255, 0, 0 };
public:
	Car(Vector2 position, int width, int height, int railIndex, int spacing);

	inline int getCurrentRailIndex() { return currentRailIndex; };
	inline void setCurrentRail(Vector2 rail) { currentRail = rail; };

	void setPathing(std::vector<Vector2> railList);
	void getCurrentRail(Vector2* rail);
	void update(float elapsedTimeSeconds);
	void draw();
};