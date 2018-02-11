#pragma once
#include "vector2.h"

class Board {
private:
	void generateThane(int multiplier);
	void handleCollision(Vector2* wall);
	void handleCollision(Vector2 pointA, Vector2 pointB);
public:
	void link(const char* path, Vector2 initialPosition, double width, double height);
	void update(int elapsedTime, int speedZone);
	void draw();
};