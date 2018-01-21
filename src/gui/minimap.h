#pragma once
#include "..\vector2.h"
#include "..\geometry.h"
#include <vector>

class Minimap {
	Vector2 position;
	double width, height;
	int color[3] = { 0, 0, 0 };

	Vector2 boardPosition, boardInitialPosition;
	double boardAngle;

	std::vector<std::vector<Vector2>> railList;
	int railColor[3] = { 255, 255, 255 };
public:
	Minimap(Vector2 pos, double w, double h) {
		position = pos;
		width = w;
		height = h;
	}

	inline void initialize(std::vector<std::vector<Vector2>> rList, Vector2 bInitialPosition) {
		boardInitialPosition = bInitialPosition;
		boardInitialPosition.shrink(10, 10);
		railList = rList;

		Vector2 firstPoint = Vector2(railList[0][0].x / 10, railList[0][0].y / 10);

		for (Vector2 &rail : railList[0]) { 
			rail.shrink(10, 10); 
			rail = rail - firstPoint;
			rail += position - Vector2(2.5, 2) + Vector2(width / 8, height / 2);
		}
		for (Vector2 &rail : railList[1]) { 
			rail.shrink(10, 10); 
			rail = rail - firstPoint;
			rail += position - Vector2(2.5, 2) + Vector2(width / 8, height / 2);
		}
	}

	inline void draw() {
		drawRect(position, width, height, color);
		drawTriangle(position + Vector2((width / 8) - 2.5, (height / 2) - 2), 5, 4, boardAngle);

		glPushMatrix();
		glTranslatef(-boardPosition.x + boardInitialPosition.x, -boardPosition.y + boardInitialPosition.y, 0);
		drawLineStrip(railList[0], railColor);
		drawLineStrip(railList[1], railColor);
		glPopMatrix();
	};

	inline void update(Vector2 bPosition, double bAngle) { 
		boardPosition = bPosition;
		boardPosition.shrink(10, 10);

		boardAngle = bAngle;
	};
};