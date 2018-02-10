#pragma once
#include "vector2.h"
#include "geometry.h"
#include <fstream>
#include <vector>

class Polylist {
public:
	double width, height;
	int color[3];
	int alpha;

	Vector2* position;
	std::vector<Vector2> vertices;
	double* angle;

	inline void setVertices(const char* filename) {
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

	inline void draw() {
		drawPolygon(*position, width, height, vertices, *angle, color, alpha);
	};

	inline void drawOutline() {
		drawLineStrip(*position, width, height, vertices, *angle, color);
	};
};