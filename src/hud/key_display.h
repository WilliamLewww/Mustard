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

	int alpha = 150;
	int releaseColor[3] = { 130, 130, 130 };
	int pressColor[3] = { 102, 153, 153 };
public:
	KeyDisplay(Vector2 position, float scale);

	void draw();
};