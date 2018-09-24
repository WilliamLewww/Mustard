#pragma once
#include <stdlib.h>
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\effects\particle_manager.h"
#include "..\bmp_polygon.h"

class Squirrel {
private:
	int color[3] = { 255, 218, 179 };
	int deadColor[3] = { 144, 55, 55 };

	Vector2 bottomRail, topRail;
	float decisionTimer = 5;
	int randomInterval;
	int randomX = 0, randomY = 0;

	bool crossRoad = false;
	int currentRail = 1;

	bool isDead = false;
public:
	BitmapPolygon polygon;

	Squirrel(Vector2 position, Vector2 bottomRail, Vector2 topRail, int width, int height);
	void update(float elapsedTimeSeconds);
	void kill();
	void draw();
};