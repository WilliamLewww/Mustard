#pragma once
#include <vector>
#include <stdlib.h>
#include "..\core\timer.h"
#include "..\camera.h"
#include "tree.h"
#include "squirrel.h"
#include "gravel.h"
#include "guard_rail.h"
#include "car.h"
#include "bike.h"
#include "pinecone.h"

class Environment {
private:
	std::vector<GuardRail> guardRailList;
	std::vector<Pinecone> pineconeList;
	std::vector<std::vector<Tree>> treeList;
	
	Vector2 visibleGuardRailRange;
	Vector2 visibleTreeRange;
	Vector2 visibleSquirrelRange;
	Vector2 visiblePineconeRange;

	float elapsedTimeSeconds;
public:
	Gravel gravel;
	std::vector<Car> carList;
	std::vector<Bike> bikeList;
	std::vector<Squirrel> squirrelList;
	
	void resetVisibleRange();

	void generateCars(std::vector<Vector2> rail, int count);
	void generateBikes(std::vector<Vector2> rail, int count, bool isLeft);
	void generateGuardRails(std::vector<Vector2> rail, int spacing, int chainMin, int chainMax, int concentration);
	void generateGravel(std::vector<std::vector<Vector2>> rail, int concentration);
	void generatePinecones(std::vector<Vector2> rail, int concentration, int scaleMin, int scaleMax);
	void generateTrees(std::vector<Vector2> rail, int concentration, int offsetY, int scaleMin, int scaleMax);
	void generateSquirrels(std::vector<std::vector<Vector2>> rail, int concentration, int scaleMin, int scaleMax);

	void update(std::vector<std::vector<Vector2>> rail);
	void draw();
	void drawUnderMountain();
};