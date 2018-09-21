#include "car.h"

Car::Car(Vector2 position, int width, int height, int railIndex, int spacing) {
	polygon.setPosition(position);
	polygon.setSize(width, height);

	polygon.setAngle(180);

	this->spacing = spacing;

	currentRailIndex = currentRailIndex;
}

void Car::setPathing(std::vector<Vector2> railList) {
	if (isLeft) {
		if (polygon.getCenter().x <= currentRail.x && currentRailIndex > spacing) {
			currentRailIndex -= spacing;
			currentRail = Vector2(railList[currentRailIndex].x, railList[currentRailIndex].y - 100);
		}
	}
	else {
		if (polygon.getCenter().x >= currentRail.x && currentRailIndex < railList.size() - 1 - spacing) {
			currentRailIndex += spacing;
			currentRail = Vector2(railList[currentRailIndex].x, railList[currentRailIndex].y - 100);
		}
	}
}

void Car::update(float elapsedTimeSeconds) {
	directionVector = Vector2((float)cos((-polygon.getAngle() * M_PI) / 180), sin((-polygon.getAngle() * M_PI) / 180));
	directionVector.normalize();
	distanceToNode = (currentRail.x - polygon.getCenter().x) / cos((-polygon.getAngle() * M_PI) / 180);

	projectedPoint = polygon.getCenter() + (directionVector * distanceToNode);

	if (isLeft) {

	}
	else {
		if (projectedPoint.y < currentRail.y) {
			polygon.addAngle(-turnSpeed * elapsedTimeSeconds);
		}
		if (projectedPoint.y > currentRail.y) {
			polygon.addAngle(turnSpeed * elapsedTimeSeconds);
		}
	}

	polygon.setPosition(polygon.getPosition() - ((directionVector * elapsedTimeSeconds) * speed));
}

void Car::draw() {
	drawing.drawRect(polygon.getPosition(), polygon.getWidth(), polygon.getHeight(), polygon.getAngle(), color);
	drawing.drawLine(polygon.getCenter(), projectedPoint);
}