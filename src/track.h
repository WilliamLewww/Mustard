#pragma once
#include "vector2.h"
#include "geometry.h"
#include <vector>

class Track {
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
	std::vector<Vector2> top;
	std::vector<Vector2> bottom;
	
	inline void draw() {
		drawLineStrip(top, color);
		drawLineStrip(bottom, color);
		// for (int x = 0; x < top.size(); x += 5) {
		// 	drawLine(top[x], bottom[x], speedZoneColor(speedZone));
		// }
	};

	inline addVertex(Vector2 position, int spacing) {
		top.push_back(Vector2(position.x, position.y));
		bottom.push_back(Vector2(position.x, position.y + spacing));
	}

	inline addVertexRelative(int topY, int spacingX, int bottomY) {
		top.push_back(Vector2(top[top.size() - 1].x + spacingX, top[top.size() - 1].y + topY));
		bottom.push_back(Vector2(bottom[bottom.size() - 1].x + spacingX, bottom[bottom.size() - 1].y + bottomY));
	}

	inline addVertexComp(int topY, int spacingX) {
		top.push_back(Vector2(top[top.size() - 1].x + spacingX, top[top.size() - 1].y + topY));
		bottom.push_back(Vector2(bottom[bottom.size() - 1].x + spacingX, bottom[bottom.size() - 1].y + topY));
	}

	inline addVertexComp(int topY, int spacingX, int offsetY, int limitTop, int limitBottom) {
		top.push_back(Vector2(top[top.size() - 1].x + spacingX, top[top.size() - 1].y + topY));
		bottom.push_back(Vector2(bottom[bottom.size() - 1].x + spacingX, top[top.size() - 1].y + offsetY + (rand() % (limitBottom - limitTop + 1) - limitTop)));
	}
};