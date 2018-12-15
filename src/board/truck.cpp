#include "truck.h"

void Truck::setAngle(double* angle) {
	boardAngle = angle;
};

void Truck::setWheelColor(int r, int g, int b) {
	wheelColor[0] = r;
	wheelColor[1] = g;
	wheelColor[2] = b;
}

void Truck::setWidth(int width) {
	leftTruck.setSize(1, width);
	rightTruck.setSize(1, width);

	leftTruck.setColor(truckColor[0], truckColor[1], truckColor[2], 255);
	rightTruck.setColor(truckColor[0], truckColor[1], truckColor[2], 255);
};

void Truck::updatePosition(Vector2 left, Vector2 right) {
	leftTruck.setPositionCentered(left);
	rightTruck.setPositionCentered(right);

	leftTruck.setAngle(*boardAngle);
	rightTruck.setAngle(*boardAngle);

	if (turnLeft && additionalAngle > -turnRadius) {
		if (additionalAngle > 0) {
			additionalAngle -= recovery * timer.getTimeSeconds();
		}
		else {
			additionalAngle -= carveStrength * timer.getTimeSeconds();
		}		
	}
	if (turnRight && additionalAngle < turnRadius) {
		if (additionalAngle < 0) {
			additionalAngle += recovery * timer.getTimeSeconds();
		}
		else {
			additionalAngle += carveStrength * timer.getTimeSeconds();
		}
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

	drawing.drawRect(leftTruck.getTopRight() - Vector2(1, 1), 3, 3, leftTruck.getAngle(), wheelColor);
	drawing.drawRect(leftTruck.getBottomRight() - Vector2(1, 1), 3, 3, leftTruck.getAngle(), wheelColor);
	drawing.drawRect(rightTruck.getTopRight() - Vector2(1, 1), 3, 3, rightTruck.getAngle(), wheelColor);
	drawing.drawRect(rightTruck.getBottomRight() - Vector2(1, 1), 3, 3, rightTruck.getAngle(), wheelColor);
};