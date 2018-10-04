#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\camera.h"

struct GravelRectangle {
	Vector2 position;
	int width, height;
};

class Gravel {
private:
	Vector2 visibleRange;

	std::vector<int> colorList;
	std::vector<std::vector<Vector2>> pebblePosition;
public:
	std::vector<GravelRectangle> gravelRectangleList;

	void resetVisibleRange();
	void generate(Vector2 rail, bool isTop, int minPebbleCount, int maxPebbleCount);
	void draw();
};