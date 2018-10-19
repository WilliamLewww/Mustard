#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\timer.h"
#include "..\core\drawing.h"
#include "..\camera.h"

struct Puddle {
	Vector2 position;
	int width, height;

	int model;
};

class Rain {
private:
	std::vector<Vector2> dropPositionList;
	int dropLength = 10, dropWidth = 2;

	int dropColor[3] = { 3, 74, 236 };

	std::vector<Puddle> puddlePosition;

	float elapsedTimeSeconds;
public:
	void update(std::vector<std::vector<Vector2>> rail);
	void draw();
};