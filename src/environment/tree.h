#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class Tree {
private:
	Vector2 position;
	float scale = 1;

	int color[3] = { 100, 100, 100 };
public:
	Tree(Vector2 position, float scale);

	void draw();
};