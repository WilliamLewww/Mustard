#include "gravel.h"

void Gravel::generate(Vector2 rail, bool isTop, int minPebbleCount, int maxPebbleCount) {
	visibleRange = Vector2(0, 0);
	pebblePosition.push_back(std::vector<Vector2>());

	int offsetY = rand() % 10;
	int spread = 75;

	int randomPebbleCount = rand() % (maxPebbleCount + 1 - minPebbleCount) + minPebbleCount;

	for (int x = 0; x < randomPebbleCount; x++) {
		if (isTop) {
			pebblePosition[pebblePosition.size() - 1].emplace_back(rail.x + (rand() % spread), rail.y + 25 + offsetY + (rand() % spread));
		}
		else {
			pebblePosition[pebblePosition.size() - 1].emplace_back(rail.x + (rand() % (spread + 25)), rail.y + offsetY - (rand() % spread));
		}
	}

	colorList.push_back(rand() % (150 + 1 - 25) + 25);
}

void Gravel::resetVisibleRange() {
	visibleRange = Vector2(0, 0);
}

void Gravel::draw() {
	// while (pebblePosition[visibleRange.x][0].x < camera.getBoundaryLeft() && visibleRange.x < pebblePosition.size()) {
	// 	visibleRange.x += 1;
	// }
	// while (pebblePosition[visibleRange.y][0].x < camera.getBoundaryRight() && visibleRange.y < pebblePosition.size()) {
	// 	visibleRange.y += 1;
	// }

	// for (int x = visibleRange.x; x < visibleRange.y; x++) {
	// 	for (Vector2 position : pebblePosition[x]) {
	// 		drawing.drawPoint(position, colorList[x]);
	// 	}
	// }
}