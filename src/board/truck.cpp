#include "truck.h"

void Truck::setAngle(double* angle) {
	boardAngle = angle;
};

void Truck::setWidth(int width) {
	leftTruck.setSize(1, width);
	rightTruck.setSize(1, width);
};

void Truck::updatePosition(Vector2 left, Vector2 right) {
	leftTruck.setPositionCentered(left);
	rightTruck.setPositionCentered(right);

	leftTruck.setAngle(*boardAngle);
	rightTruck.setAngle(*boardAngle);

	if (turnLeft && additionalAngle > -15) {
		additionalAngle -= carveStrength * timer.getTimeSeconds();
		
	}
	if (turnRight && additionalAngle < 15) {
		additionalAngle += carveStrength * timer.getTimeSeconds();
	}

	if (!turnRight && !turnLeft) {
		if (additionalAngle > 0) {
			if (additionalAngle - recovery * timer.getTimeSeconds() <= 0) {
				additionalAngle = 0;
			}
			else {
				additionalAngle -= recovery * timer.getTimeSeconds();
			}
		}
		if (additionalAngle < 0) {
			if (additionalAngle + recovery * timer.getTimeSeconds() > 0) {
				additionalAngle = 0;
			}
			else {
				additionalAngle += recovery * timer.getTimeSeconds();
			}
		}
	}

	leftTruck.addAngle(additionalAngle);
	rightTruck.addAngle(-additionalAngle);
};

void Truck::draw() {
	leftTruck.draw();
	rightTruck.draw();

	drawing.drawRect(leftTruck.getTopRight() - Vector2(1, 1), 3, 3, leftTruck.getAngle());
	drawing.drawRect(leftTruck.getBottomRight() - Vector2(1, 1), 3, 3, leftTruck.getAngle());
	drawing.drawRect(rightTruck.getTopRight() - Vector2(1, 1), 3, 3, rightTruck.getAngle());
	drawing.drawRect(rightTruck.getBottomRight() - Vector2(1, 1), 3, 3, rightTruck.getAngle());
};