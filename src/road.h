#pragma once
#include <vector>
#include "core\vector2.h"
#include "core\drawing.h"
#include "core\configuration.h"
#include "camera.h"

class Road {
private:
	std::vector<std::vector<Vector2>> roadPolygonList;
	std::vector<float> roadColorList;

	float roadColor = 40;

public:
	void generate(std::vector<std::vector<Vector2>> railList, std::vector<Vector2> speedZones, int visibleRangeX, int visibleRangeY);
	void clear();
	void draw(int visibleRangeX);
};