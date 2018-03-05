#pragma once
#include "..\vector2.h"
#include "..\drawing.h"
#include <vector>

class Minimap {
	Vector2 position;
	double width, height;
	int color[3] = { 0, 0, 0 };
	int alpha = 255;

	Vector2 trianglePosition;

	double scaleFactor = 15;
	
	Vector2 boardPosition, boardInitialPosition;
	double boardAngle;

	std::vector<std::vector<Vector2>> railList;
	int railColor[3] = { 255, 255, 255 };

	void setVisibleRange();
	std::vector<Vector2> getVisibleRail(int index);
public:
	Vector2 visibleRange = Vector2(0, 0);

	Minimap(Vector2 pos, double w, double h);

	void initialize(std::vector<std::vector<Vector2>> rList, Vector2 bInitialPosition);
	void resetVisibleRange();
	void draw();
	void update(Vector2 bPosition, double bAngle);
};