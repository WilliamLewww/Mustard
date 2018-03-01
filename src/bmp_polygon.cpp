#include "bmp_polygon.h"

void BitmapPolygon::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

void BitmapPolygon::setColor(int red, int green, int blue, int alpha) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	this->alpha = alpha;
}

void BitmapPolygon::setVerticesFromFile(const char* filename) {
	std::ifstream fin(filename);
	Vector2 temp_vertex = Vector2(-1, -1);

	int x;
	while (fin >> x) {
		if (temp_vertex.y != -1) { vertices.push_back(temp_vertex); temp_vertex = Vector2(-1, -1); }
		if (temp_vertex.x == -1) { temp_vertex.x = x; }
		else { temp_vertex.y = x; }
	}

	vertices.push_back(temp_vertex);

	fin.close();
};

void BitmapPolygon::drawOutline() {
	drawing.drawLineStrip(position, width, height, vertices, angle, color);
};