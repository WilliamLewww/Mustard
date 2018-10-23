#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\timer.h"
#include "..\core\drawing.h"
#include "..\core\configuration.h"
#include "..\camera.h"

class Rain {
private:
	std::vector<std::vector<Vector2>> puddleVertexList;
	int puddleColor[3] = { 23, 94, 255 };
	int puddleAlpha = 80;

	std::vector<Vector2> dropPositionList;
	int dropLength = 10, dropWidth = 2;
	int dropColor[3] = { 3, 74, 236 };

	float elapsedTimeSeconds;
public:
	void generate(std::vector<Vector2> rail, int concentration);
	void update();
	void drawStatic();
	void draw();
};