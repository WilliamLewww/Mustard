#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\bmp_polygon.h"

class Squirrel {
private:
	Vector2 position;
	int width, height;

	Vector2 homePosition;
	float decisionTimer = 0;
public:
	Squirrel(Vector2 position, Vector2 homePosition, int width, int height);

	void update(float elapsedTimeSeconds);
	void draw();
};