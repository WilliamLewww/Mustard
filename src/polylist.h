#pragma once
#include "vector2.h"
#include "geometry.h"
#include <iostream>
#include <fstream>
#include <vector>

class Polylist {
public:
	Vector2 position = Vector2(25, 100);
	std::vector<Vector2> vertices;

	int color[3] = { 255, 255, 255 };
	int alpha = 255;

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
		drawPolygon(position, vertices, color, alpha);
	};
};