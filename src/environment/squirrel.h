#pragma once
#include <stdlib.h>
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\bmp_polygon.h"

class Squirrel {
private:
	int color[3] = { 255, 218, 179 };
	int deadColor[3] = { 134, 45, 45 };

	Vector2 bottomRail, topRail;
	float decisionTimer = 5;
	int randomInterval;
	int randomX = 0, randomY = 0;

	bool crossRoad = false;
	int currentRail = 1;

	bool dead = false;
public:
	BitmapPolygon polygon;

	inline void setDead(bool isDead) { dead = isDead; };

	Squirrel(Vector2 position, Vector2 bottomRail, Vector2 topRail, int width, int height);
	void update(float elapsedTimeSeconds);
	void draw();
};