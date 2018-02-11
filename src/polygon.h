#pragma once
#include "vector2.h"
#include "draw_functions.h"
#include <fstream>
#include <vector>

class Polygon {
private:
	Vector2 position;
	double width, height;
	double angle;

	std::vector<Vector2> vertices;

	int color[3];
	int alpha;
public:
	void setColor(int red, int green, int blue, int alpha);
	void setVerticesFromFile(const char* filename);
	void draw();
	void drawOutline();
};