#pragma once
#include "minimap.h"
#include <vector>

class GUI {
	Minimap minimap = Minimap(Vector2(5, 5), 200, 200);
public:
	void draw();
	void initializeMinimap(std::vector<std::vector<Vector2>> railList, Vector2 boardInitialPosition, Vector2 position, int width, int height);
	void updateMinimap(Vector2 position, double angle);
	void resetMinimap();
};   