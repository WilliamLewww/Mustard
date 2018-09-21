#pragma once
#include "..\core\vector2.h"
#include "..\bmp_polygon.h"

class Car {
private:
	Vector2 directionVector;
	float distanceToNode;

	Vector2 projectedPoint;

	Vector2 currentRail;
	int currentRailIndex;

	int spacing;

	float speed = 0, turnSpeed = 60;
	float speedMax = 85, speedMin = 25;
	float speedReduction = 75;

	float differenceMagnitude = 8;

	bool isLeft = false;
	int colorIndex;
public:
	BitmapPolygon polygon;

	Car(Vector2 position, int railIndex, int spacing);

	void setPathing(std::vector<Vector2> railList);
	void getCurrentRail(Vector2* rail);
	void update(float elapsedTimeSeconds);
	void draw();

	bool handleCollision(BitmapPolygon polygon);
};