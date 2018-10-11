#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\core\input.h"

struct DispayBox {
	Vector2 position;
	int width, height;
};

class KeyDisplay {
private:
	std::vector<DispayBox> boxList;

	float scale;

	int alpha = 255;
	int releaseColor[3] = { 255, 255, 255 };
	int pressColor[3] = { 150, 150, 150 };
public:
	KeyDisplay(Vector2 position, float scale);

	void draw();
};