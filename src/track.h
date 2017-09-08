#pragma once
#include "vector2.h"
#include "geometry.h"
#include <vector>

class Track {
	std::vector<Vector2> speedZones;
	
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
	std::vector<std::vector<Vector2>> railList;
	
	inline void draw() {
		for (std::vector<Vector2> segment : railList) {
			drawLineStrip(segment, color);
		}
		// for (int x = 0; x < top.size(); x += 5) {
		// 	drawLine(top[x], bottom[x], speedZoneColor(speedZone));
		// }
	};

	inline addRail(int count) {
		for (int x = 0; x < count; x++) {
			railList.push_back(std::vector<Vector2>());
		}
	};

	inline addVertex(int indexTop, int indexBottom, Vector2 position, int spacing) {
		railList[indexTop].push_back(Vector2(position.x, position.y));
		railList[indexBottom].push_back(Vector2(position.x, position.y + spacing));
	};

	inline addVertexRelative(int indexTop, int indexBottom, int topY, int spacingX, int bottomY) {
		railList[indexTop].push_back(Vector2(railList[indexTop][railList[indexTop].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + topY));
		railList[indexBottom].push_back(Vector2(railList[indexBottom][railList[indexBottom].size() - 1].x + spacingX, railList[indexBottom][railList[indexBottom].size() - 1].y + bottomY));
	};

	inline addVertexComp(int indexTop, int indexBottom, int topY, int spacingX) {
		railList[indexTop].push_back(Vector2(railList[indexTop][railList[indexTop].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + topY));
		railList[indexBottom].push_back(Vector2(railList[indexBottom][railList[indexBottom].size() - 1].x + spacingX, railList[indexBottom][railList[indexBottom].size() - 1].y + topY));
	};

	inline addVertexComp(int indexTop, int indexBottom, int topY, int spacingX, int offsetY, int limitTop, int limitBottom) {
		railList[indexTop].push_back(Vector2(railList[indexTop][railList[indexTop].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + topY));
		railList[indexBottom].push_back(Vector2(railList[indexBottom][railList[indexBottom].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + offsetY + (rand() % (limitBottom - limitTop + 1) - limitTop)));
	};
};