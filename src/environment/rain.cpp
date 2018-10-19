#include "rain.h"

void Rain::update(std::vector<std::vector<Vector2>> rail) {
	elapsedTimeSeconds = timer.getTimeSeconds();
}

void Rain::draw() {
	for (Vector2 position : dropPositionList) {
		drawing.drawRect(position, dropWidth, dropLength, dropColor, 125);
	}
}