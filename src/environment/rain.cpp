#include "rain.h"

void Rain::generate(std::vector<Vector2> rail, int concentration) {
	for (int x = 0; x < configuration.getScreenWidth(); x += 12) {
		for (int y = 0; y < configuration.getScreenHeight(); y += 12) {
			if (rand() % 2 == 0) {
				dropPositionList.push_back(Vector2(x, y));
			}
		}
	}

	std::vector<Vector2> vertexList;
	for (int x = 15; x < rail.size(); x++) {
		if (rand() % concentration == 0) {
			vertexList.push_back(Vector2(rail[x].x + (rand() % 15), rail[x].y - 40 - (rand() % 15)));
			vertexList.push_back(Vector2(rail[x].x + 50 + (rand() % 15), rail[x].y - 40 - (rand() % 15)));
			vertexList.push_back(Vector2(rail[x].x + 75 + (rand() % 15), rail[x].y - 65 - (rand() % 15)));
			vertexList.push_back(Vector2(rail[x].x + 50 + (rand() % 15), rail[x].y - 90 - (rand() % 15)));
			vertexList.push_back(Vector2(rail[x].x + (rand() % 15), rail[x].y - 90 - (rand() % 15)));
			vertexList.push_back(Vector2(rail[x].x - 25 + (rand() % 15), rail[x].y - 65 - (rand() % 15)));

			puddleVertexList.push_back(vertexList);
			vertexList.clear();
		}
	}
}

void Rain::update() {
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

void Rain::drawStatic() {
	for (Vector2 position : dropPositionList) {
		drawing.drawRect(position, dropWidth, dropLength, dropColor, 125);
	}
}

void Rain::draw() {
	for (std::vector<Vector2> vertexList : puddleVertexList) {
		drawing.drawPolygon(vertexList, puddleColor, puddleAlpha);
	}
}