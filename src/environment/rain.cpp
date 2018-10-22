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

	for (Vector2 &position : dropPositionList) {
		position.x -= 250 * elapsedTimeSeconds;
		position.y += 500 * elapsedTimeSeconds;

		if (position.x < 0) { position.x = configuration.getScreenWidth(); }
		if (position.y > configuration.getScreenHeight()) { position.y = 0; }
	}
}

void Rain::draw() {
	for (Vector2 position : dropPositionList) {
		drawing.drawRect(position, dropWidth, dropLength, dropColor, 125);
	}
}