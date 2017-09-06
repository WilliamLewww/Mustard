#pragma once
#include "vector2.h"
#include "geometry.h"
#include <vector>

class Track {
	std::vector<Vector2> top;
	std::vector<Vector2> bottom;

	double speedZone = 15;
	int color[3] = { 0, 0, 255 };

	inline int* speedZoneColor(int speed) {
		int* tempColor = (int*)malloc(3 * sizeof(int));
		if (speed < 10) {
			tempColor[0] = 0;
			tempColor[1] = 255;
			tempColor[2] = 0;
			return tempColor;
		}
		if (speed < 20) {
			tempColor[0] = 255;
			tempColor[1] = 153;
			tempColor[2] = 0;
			return tempColor;
		}
		if (speed < 30) {
			tempColor[0] = 255;
			tempColor[1] = 0;
			tempColor[2] = 0;
			return tempColor;
		}
	}
public:
	inline void draw() {
		drawLineStrip(top, color);
		drawLineStrip(bottom, color);
		for (int x = 0; x < top.size(); x += 2) {
			drawLine(top[x], bottom[x], speedZoneColor(speedZone));
		}
	};

	inline addVertex(Vector2 position, int spacing) {
		top.push_back(Vector2(position.x, position.y));
		bottom.push_back(Vector2(position.x, position.y + spacing));
	}

	inline addVertexRelative(int offsetY, int spacingX, int spacingY) {
		top.push_back(Vector2(top[top.size() - 1].x + spacingX, top[top.size() - 1].y + offsetY));
		bottom.push_back(Vector2(top[top.size() - 2].x + spacingX, top[top.size() - 2].y + offsetY + spacingY));
	}
};