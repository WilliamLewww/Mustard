#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class SplitsDisplay {
private:
	int color[3] = { 255, 255, 255 };

public:
	Vector2 position;
	int width, height;
	
	SplitsDisplay(Vector2 position, int width, int height);
	void draw();
};