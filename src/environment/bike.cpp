#include "bike.h"

int bikeColor[5][3] = { {255,0,102}, {51,204,51}, {0,204,255}, {204,0,255}, {102,153,0} };

Bike::Bike(Vector2 position, int railIndex) {
	polygon.setPosition(position);
	polygon.setSize(25, 5);

	polygon.setAngle(180);
	colorIndex = rand() % 6;

	currentRailIndex = railIndex;
}

void Bike::setPathing(std::vector<Vector2> railList) {
	if (currentRailIndex > railList.size() - 1) {
		polygon.setAngle(180);

		speed = 0;
		currentRailIndex = 3;
		polygon.setPosition(Vector2(railList[currentRailIndex].x, railList[currentRailIndex].y + 25));
		currentRail = Vector2(railList[currentRailIndex].x, railList[currentRailIndex].y + 25);
	}

	if (polygon.getCenter().x >= currentRail.x && currentRailIndex < railList.size() - 1) {
		currentRailIndex += 1;
		currentRail = Vector2(railList[currentRailIndex].x, railList[currentRailIndex].y + 25);
	}
}

void Bike::update(float elapsedTimeSeconds) {

	directionVector = Vector2((float)cos((-polygon.getAngle() * M_PI) / 180), sin((-polygon.getAngle() * M_PI) / 180));
	directionVector.normalize();
	distanceToNode = (currentRail.x - polygon.getCenter().x) / cos((-polygon.getAngle() * M_PI) / 180);

	projectedPoint = polygon.getCenter() + (directionVector * distanceToNode);

	if (projectedPoint.y <= currentRail.y + 5) {
		polygon.addAngle(-turnSpeed * elapsedTimeSeconds);
	}

	if (projectedPoint.y >= currentRail.y - 5) {
		polygon.addAngle(turnSpeed * elapsedTimeSeconds);
	}

	polygon.setPosition(polygon.getPosition() - ((directionVector * elapsedTimeSeconds) * speed));
}

void Bike::draw() {
	drawing.drawRect(polygon.getPosition(), polygon.getWidth(), polygon.getHeight(), polygon.getAngle(), bikeColor[colorIndex]);
	//drawing.drawLine(polygon.getCenter(), projectedPoint);
}

bool Bike::handleCollision(BitmapPolygon polygon) {
	if (polygon.checkCollision(polygon) == true) {
		return true;
	}

	return false;
}