#pragma once
#include "..\core\vector2.h"
#include "..\bmp_polygon.h"

class Bike {
private:
	Vector2 directionVector;
	float distanceToNode;

	Vector2 projectedPoint;

	Vector2 currentRail;
	int currentRailIndex;

	float speed = 50, turnSpeed = 150;

	bool isLeft = false;
	int colorIndex;
public:
	BitmapPolygon polygon;

	Bike(Vector2 position, int railIndex);

	void setPathing(std::vector<Vector2> railList);
	void getCurrentRail(Vector2* rail);
	void update(float elapsedTimeSeconds);
	void draw();

	bool handleCollision(BitmapPolygon polygon);
};