#pragma once
#include "..\vector2.h"
#include "..\geometry.h"
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
public:
	Vector2 visibleRange = Vector2(0, 0);

	Minimap(Vector2 pos, double w, double h) {
		position = pos;
		width = w;
		height = h;
	}

	inline void initialize(std::vector<std::vector<Vector2>> rList, Vector2 bInitialPosition) {
		trianglePosition = position + Vector2((width / 8) - 2.5, (height / 2) - 2);
		boardInitialPosition = bInitialPosition;
		boardInitialPosition.shrink(scaleFactor, scaleFactor);
		railList = rList;

		Vector2 firstPoint = Vector2(railList[0][0].x / scaleFactor, railList[0][0].y / scaleFactor);

		for (Vector2 &rail : railList[0]) { 
			rail.shrink(scaleFactor, scaleFactor); 
			rail = rail - firstPoint;
			rail += position - Vector2(2.5, 2) + Vector2(width / 8, height / 2);
		}
		for (Vector2 &rail : railList[1]) { 
			rail.shrink(scaleFactor, scaleFactor); 
			rail = rail - firstPoint;
			rail += position - Vector2(2.5, 2) + Vector2(width / 8, height / 2);
		}
	}
	
	inline void setVisibleRange() {
		for (int x = visibleRange.x; x < railList[0].size(); x++) {
			if (railList[0][x].x < position.x + (boardPosition.x - boardInitialPosition.x)) { visibleRange.x += 1; }
			if (railList[0][x].x < (position.x + width) + (boardPosition.x - boardInitialPosition.x)) { visibleRange.y = x; }
			else { break; }
		}
	};

	inline std::vector<Vector2> getVisibleRail(int index) {
		if (visibleRange.x == 0) {
			return std::vector<Vector2>(railList[index].begin() + visibleRange.x + 1, railList[index].begin() + visibleRange.y);
		}
		return std::vector<Vector2>(railList[index].begin() + visibleRange.x, railList[index].begin() + visibleRange.y);
	};

	inline void resetVisibleRange() { 
		visibleRange = Vector2(0,0);
	};

	inline void draw() {
		setVisibleRange();
		
		drawRect(position, width, height, color);
		drawTriangle(trianglePosition, 5, 4, boardAngle);

		glPushMatrix();
		glTranslatef(-boardPosition.x + boardInitialPosition.x, -boardPosition.y + boardInitialPosition.y, 0);
		drawLineStrip(getVisibleRail(0), railColor, alpha);
		drawLineStrip(getVisibleRail(1), railColor, alpha);
		glPopMatrix();
	};

	inline void update(Vector2 bPosition, double bAngle) { 
		boardPosition = bPosition;
		boardPosition.shrink(scaleFactor, scaleFactor);

		boardAngle = bAngle;
	};
};