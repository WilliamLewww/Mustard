#include "environment.h"

void Environment::generateTrees(std::vector<Vector2> rail, int concentration, int offsetY, int scaleMin, int scaleMax) {
	visibleTreeRange = Vector2(0, 0);
	std::vector<Tree> tempTreeList;

	for (int x = 0; x < rail.size(); x++) {
		if (rand() % concentration == 0) {
			tempTreeList.emplace_back(Vector2(rail[x].x, rail[x].y + offsetY), rand() % (scaleMax + 1 - scaleMin) + scaleMin);
		}
	}

	treeList.push_back(tempTreeList);
	tempTreeList.clear();
}

void Environment::resetVisibleRange() {
	visibleTreeRange = Vector2(0, 0);
}

void Environment::draw() {
	while (treeList[0][visibleTreeRange.x].position.x < camera.getBoundaryLeft()) {
		visibleTreeRange.x += 1;
	}
	while (treeList[0][visibleTreeRange.y].position.x < camera.getBoundaryRight()) {
		visibleTreeRange.y += 1;
	}

	for (std::vector<Tree> treeListTotal : treeList) {
		for (int x = visibleTreeRange.x; x < visibleTreeRange.y; x++) {
			treeListTotal[x].draw();
		}
	}
}