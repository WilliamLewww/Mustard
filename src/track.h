#pragma once
#include "vector2.h"
#include "drawing.h"
#include "camera.h"
#include <vector>

class Track {
	std::vector<std::vector<Vector2>> roadPolygonList;

	int sideColor[3] = { 225, 225, 225 };
	int centerColor[3] = { 255, 173, 71 };
	int roadColor[3] = { 60, 60, 60 };

	int* speedZoneColor(int speed);
public:
	std::vector<std::vector<Vector2>> railList;
	std::vector<Vector2> speedZones;
	Vector2 visibleRange = Vector2(0,0);

	void initialize();

	void resetVisibleRange();
	void generateGroundPolygons();
	void updateVisibleRange();
	std::vector<Vector2> getVisibleRail(int side);
	void draw(int generationStyle, bool drawDetails);
	void addSpeedZone(int node, int speed);
	void addVertex(Vector2 position, int spacing);
	void addVertexSingle(int index, Vector2 position);
	void addVertexRelative(int topY, int spacingX, int bottomY);
	void addVertexRelativeTop(int index, int topY, int spacingX);
	void addVertexRelativeBottom(int index, int slope);
	void addVertexComp(int topY, int spacingX);
	void addVertexComp(int topY, int spacingX, int offsetY, int limitTop, int limitBottom);
};