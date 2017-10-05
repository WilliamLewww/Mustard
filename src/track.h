#pragma once
#include "vector2.h"
#include "geometry.h"
#include "camera.h"
#include <vector>

class Track {
	int color[3] = { 0, 0, 255 };

	inline int* speedZoneColor(int speed) {
		int* tempColor = (int*)malloc(3 * sizeof(int));
		tempColor[0] = ((double)speed / 50) * 255;
		tempColor[1] = ((50 - (double)speed) / 50) * 255;
		tempColor[2] = 0;

		return tempColor;
	}
public:
	std::vector<std::vector<Vector2>> railList;
	std::vector<Vector2> speedZones;

	std::vector<std::vector<Vector2>> roadPolygonList;

	Vector2 visibleRange = Vector2(0,0);

	inline resetVisibleRange() { visibleRange = Vector2(0,0); roadPolygonList.clear(); }

	inline void generateGroundPolygons() {
		for (int x = visibleRange.x; x < visibleRange.y; x++) {
			std::vector<Vector2> tempPolygon;
			if (x > 0 && (roadPolygonList.size() == 0 || roadPolygonList[roadPolygonList.size() - 1][0].x < railList[0][x].x)) {
				tempPolygon.emplace_back(railList[0][x]);
				tempPolygon.emplace_back(railList[0][x - 1]);
				tempPolygon.emplace_back(railList[1][x - 1]);
				tempPolygon.emplace_back(railList[1][x]);

				roadPolygonList.push_back(tempPolygon);
			}
		}

		for (int x = 0; x < roadPolygonList.size(); x++) {
			if (roadPolygonList[x][0].x < visibleFrame.sLeft()) {
				roadPolygonList.erase(roadPolygonList.begin());
				x -= 1;
			}
			else { break; }
		}
	}

	inline setVisibleRange() {
		for (int x = visibleRange.x; x < railList[0].size(); x++) {
			if (railList[0][x].x < visibleFrame.sLeft()) { visibleRange.x += 1; }
			if (railList[0][x].x < visibleFrame.sRight()) { visibleRange.y = x; }
			else { break; }
		}
	};
	
	inline void draw() {
		setVisibleRange();
		generateGroundPolygons();

		for (std::vector<Vector2> polygon : roadPolygonList) {
			drawPolygon(polygon, color, 50);
		}

		for (std::vector<Vector2> segment : railList) {
			drawLineStrip(std::vector<Vector2>(segment.begin() + visibleRange.x, segment.begin() + visibleRange.y), color);
		}

		for (Vector2 speedZone : speedZones) {
			if (railList[0][speedZone.x].x < visibleFrame.sRight() && railList[0][speedZone.x].x > visibleFrame.sLeft()) {
				drawLine(Vector2(railList[0][speedZone.x].x, railList[0][speedZone.x].y),
						 Vector2(railList[1][speedZone.x].x, railList[1][speedZone.x].y),
						 speedZoneColor(speedZone.y), 100);
			}
		}
	};

	inline addRail(int count) {
		for (int x = 0; x < count; x++) {
			railList.push_back(std::vector<Vector2>());
		}
	};

	inline addSpeedZone(int node, int speed) {
		speedZones.push_back(Vector2(node, speed));
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