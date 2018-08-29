#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class Tree {
private:
	float scale = 1;

	int color[3] = { 127, 153, 178 };
public:
	Vector2 position;
	Tree(Vector2 position, float scale);

	void draw();
};