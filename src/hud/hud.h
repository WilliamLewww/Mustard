#pragma once
#include <vector>
#include "..\core\configuration.h"
#include "minimap.h"

class HUD {
	Minimap minimap = Minimap(Vector2(5, 5), 200, 200);
public:
	void draw();
	void initializeMinimap(std::vector<std::vector<Vector2>> railList, Vector2 boardInitialPosition, Vector2 position, int width, int height);
	void updateMinimap(Vector2 position, double angle);
	void resetMinimap();
};   