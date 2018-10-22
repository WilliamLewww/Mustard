#include "rain.h"

void Rain::generate() {
	for (int x = 0; x < configuration.getScreenWidth(); x += 25) {
		for (int y = 0; y < configuration.getScreenHeight(); y += 25) {
			dropPositionList.push_back(Vector2(x, y));
		}
	}
}

void Rain::update(std::vector<std::vector<Vector2>> rail) {
	elapsedTimeSeconds = timer.getTimeSeconds();

	for (int x = 0; x < dropPositionList.size(); x++) {
		dropPositionList[x].x -= 250 * elapsedTimeSeconds;

		if (x % 2 == 0) {
			dropPositionList[x].x -= 25 * elapsedTimeSeconds;
			dropPositionList[x].y += 100 * elapsedTimeSeconds;
		}

		if (x % 3 == 0) {
			dropPositionList[x].x -= 50 * elapsedTimeSeconds;
			dropPositionList[x].y += 200 * elapsedTimeSeconds;
		}

		if (x % 5 == 0) {
			dropPositionList[x].x -= 75 * elapsedTimeSeconds;
			dropPositionList[x].y += 250 * elapsedTimeSeconds;
		}

		dropPositionList[x].y += 300 * elapsedTimeSeconds;

		if (dropPositionList[x].x < 0) { dropPositionList[x].x = configuration.getScreenWidth(); }
		if (dropPositionList[x].y > configuration.getScreenHeight()) { dropPositionList[x].y = 0; }
	}
}

void Rain::draw() {
	for (Vector2 position : dropPositionList) {
		drawing.drawRect(position, dropWidth, dropLength, dropColor, 125);
	}
}