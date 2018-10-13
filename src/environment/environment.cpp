#include "environment.h"

void Environment::generatePinecones(std::vector<Vector2> rail, int concentration, int scaleMin, int scaleMax) {
	visiblePineconeRange = Vector2(0,0);

	for (int x = 10; x < rail.size(); x++) {
		if (rand() % concentration == 0) {
			pineconeList.emplace_back(Vector2(rail[x].x, rail[x].y - 25 - (rand() % 70)), rand() % (scaleMax + 1 - scaleMin) + scaleMin);
		}
	}
}

void Environment::generateGravel(std::vector<std::vector<Vector2>> railList, int concentration) {
	for (int x = 0; x < railList[0].size(); x++) {
		if (rand() % concentration == 0) { gravel.generate(railList[1][x], false, concentration + 50, concentration + 150); }
	}
}

void Environment::generateBikes(std::vector<Vector2> rail, int count, bool isLeft) {
	int randomIndex;

	std::vector<int> indexList;
	bool isTooClose = true;

	for (int x = 0; x < count; x++) {
		isTooClose = true;

		while (isTooClose == true) {
			isTooClose = false;

			randomIndex = rand() % (rail.size() - 1 + 1 - 5) + 5;

			for (int index : indexList) {
				if (abs(randomIndex - index) < 5) {
					isTooClose = true;
				}
			}
		}

		if (isLeft) {
			bikeList.emplace_back(Vector2(rail[randomIndex].x, rail[randomIndex].y), randomIndex, isLeft);
		}
		else {
			bikeList.emplace_back(Vector2(rail[randomIndex].x, rail[randomIndex].y), randomIndex, isLeft);
		}
		indexList.emplace_back(randomIndex);
	}
}

void Environment::generateCars(std::vector<Vector2> rail, int count) {
	int spacing = 7;
	int randomIndex;

	std::vector<int> indexList;
	bool isTooClose = true;

	for (int x = 0; x < count; x++) {
		isTooClose = true;

		while (isTooClose == true) {
			isTooClose = false;

			randomIndex = rand() % (rail.size() - spacing + 1 - 3) + 3;

			for (int index : indexList) {
				if (abs(randomIndex - index) < 20) {
					isTooClose = true;
				}
			}
		}

		carList.emplace_back(Vector2(rail[randomIndex].x, rail[randomIndex].y - 50), randomIndex, spacing);
		indexList.emplace_back(randomIndex);
	}
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
	visiblePineconeRange = Vector2(0, 0);
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

	for (Bike& bike : bikeList) {
		if (!bike.isLeft) {
			bike.setPathing(rail[0]);
		}
		else {
			bike.setPathing(rail[1]);
		}
		bike.update(elapsedTimeSeconds);
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

	while (pineconeList[visiblePineconeRange.x].getPosition().x < camera.getBoundaryLeft()) {
		visiblePineconeRange.x += 1;
	}
	while (pineconeList[visiblePineconeRange.y].getPosition().x < camera.getBoundaryRight()) {
		visiblePineconeRange.y += 1;
	}

	for (std::vector<Tree> treeListTotal : treeList) {
		for (int x = visibleTreeRange.x; x < visibleTreeRange.y; x++) {
			treeListTotal[x].draw();
		}
	}

	for (int x = visiblePineconeRange.x; x < visiblePineconeRange.y; x++) {
		pineconeList[x].draw();
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

	for (Bike bike : bikeList) {
		bike.draw();
	}
}

void Environment::drawUnderMountain() {
	gravel.draw();
}