#include "environment.h"

void Environment::generateGravel(std::vector<std::vector<Vector2>> railList, int concentration) {
	for (int x = 0; x < railList[0].size(); x++) {
		if (rand() % concentration == 0) { gravel.generate(railList[1][x], false, concentration + 50, concentration + 150); }
	}
}

void Environment::generateCars(std::vector<Vector2> rail, int concentration) {
	carList.emplace_back(Vector2(rail[3].x, rail[3].y - 50), 50, 20, 3, 10);
}

void Environment::generateGuardRails(std::vector<Vector2> rail, int spacing, int chainMin, int chainMax, int concentration) {
	visibleGuardRailRange = Vector2(0, 0);
	bool createChain = false;
	int chainSize;
	int currentChainSize = 0;

	for (int x = 0; x < rail.size() - spacing; x += spacing) {
		if (rand() % concentration == 0 && createChain == false) {
			chainSize = rand() % (chainMax + 1 - chainMin) + chainMin;
			currentChainSize = 0;
			createChain = true;
		}
		if (createChain) {
			guardRailList.emplace_back(rail[x], rail[x + spacing]);
			currentChainSize += 1;

			if (currentChainSize == chainSize) {
				createChain = false;
			}
		}
	}
}

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

void Environment::generateSquirrels(std::vector<std::vector<Vector2>> rail, int concentration, int scaleMin, int scaleMax) {
	visibleSquirrelRange = Vector2(0, 0);

	for (int x = 0; x < rail[1].size(); x++) {
		if (rand() % concentration == 0) {
			int randomScale = rand() % (scaleMax + 1 - scaleMin) + scaleMin;
			squirrelList.emplace_back(Vector2(rail[1][x].x, rail[1][x].y + 50), Vector2(rail[1][x].x, rail[1][x].y), Vector2(rail[0][x].x, rail[0][x].y), randomScale, randomScale);
		}
	}
}

void Environment::resetVisibleRange() {
	gravel.resetVisibleRange();

	visibleTreeRange = Vector2(0, 0);
	visibleSquirrelRange = Vector2(0, 0);
	visibleGuardRailRange = Vector2(0, 0);
}

void Environment::update(std::vector<std::vector<Vector2>> rail) {
	elapsedTimeSeconds = timer.getTimeSeconds();
	
	for (int x = visibleSquirrelRange.x; x < visibleSquirrelRange.y; x++) {
		squirrelList[x].update(elapsedTimeSeconds);
	}

	for (Car& car : carList) {
		car.setPathing(rail[1]);
		car.update(elapsedTimeSeconds);
	}
}

void Environment::draw() {
	while (treeList[0][visibleTreeRange.x].position.x < camera.getBoundaryLeft()) {
		visibleTreeRange.x += 1;
	}
	while (treeList[0][visibleTreeRange.y].position.x < camera.getBoundaryRight()) {
		visibleTreeRange.y += 1;
	}

	while (squirrelList[visibleSquirrelRange.x].polygon.getX() < camera.getBoundaryLeft()) {
		visibleSquirrelRange.x += 1;
	}

	while (squirrelList[visibleSquirrelRange.y].polygon.getX() < camera.getBoundaryRight()) {
		visibleSquirrelRange.y += 1;
	}

	while (guardRailList[visibleGuardRailRange.x].nodeA.x < camera.getBoundaryLeft()) {
		visibleGuardRailRange.x += 1;
	}
	while (guardRailList[visibleGuardRailRange.y].nodeB.x < camera.getBoundaryRight()) {
		visibleGuardRailRange.y += 1;
	}

	for (std::vector<Tree> treeListTotal : treeList) {
		for (int x = visibleTreeRange.x; x < visibleTreeRange.y; x++) {
			treeListTotal[x].draw();
		}
	}

	for (int x = visibleGuardRailRange.x; x < visibleGuardRailRange.y; x++) {
		guardRailList[x].draw();
	}

	for (int x = visibleSquirrelRange.x; x < visibleSquirrelRange.y; x++) {
		squirrelList[x].draw();
	}

	for (Car car : carList) {
		car.draw();
	}
}

void Environment::drawUnderMountain() {
	gravel.draw();
}