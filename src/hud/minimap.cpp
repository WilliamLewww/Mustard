#include "minimap.h"

Minimap::Minimap(Vector2 pos, double w, double h) {
	position = pos;
	width = w;
	height = h;
}

void Minimap::initialize(std::vector<std::vector<Vector2>> rList, Vector2 bInitialPosition) {
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

void Minimap::setVisibleRange() {
	for (int x = visibleRange.x; x < railList[0].size(); x++) {
		if (railList[0][x].x < position.x + (boardPosition.x - boardInitialPosition.x)) { visibleRange.x += 1; }
		if (railList[0][x].x < (position.x + width) + (boardPosition.x - boardInitialPosition.x)) { visibleRange.y = x; }
		else { break; }
	}
};

std::vector<Vector2> Minimap::getVisibleRail(int index) {
	if (visibleRange.x == 0) {
		return std::vector<Vector2>(railList[index].begin() + visibleRange.x + 1, railList[index].begin() + visibleRange.y);
	}
	return std::vector<Vector2>(railList[index].begin() + visibleRange.x, railList[index].begin() + visibleRange.y);
};

void Minimap::resetVisibleRange() { 
	visibleRange = Vector2(0,0);
};

void Minimap::draw() {
	setVisibleRange();
	
	drawing.drawRect(position, width, height, color);
	drawing.drawTriangle(trianglePosition, 5, 4, boardAngle);

	glPushMatrix();
	glTranslatef(-boardPosition.x + boardInitialPosition.x, -boardPosition.y + boardInitialPosition.y, 0);
	drawing.drawLineStrip(getVisibleRail(0), railColor, alpha);
	drawing.drawLineStrip(getVisibleRail(1), railColor, alpha);
	glPopMatrix();
};

void Minimap::update(Vector2 bPosition, double bAngle) { 
	boardPosition = bPosition;
	boardPosition.shrink(scaleFactor, scaleFactor);

	boardAngle = bAngle;
};