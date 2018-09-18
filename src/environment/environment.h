#pragma once
#include <vector>
#include <stdlib.h>
#include "..\core\timer.h"
#include "..\camera.h"
#include "tree.h"
#include "squirrel.h"
#include "gravel.h"

class Environment {
private:
	Gravel gravel;

	std::vector<std::vector<Tree>> treeList;

	Vector2 visibleTreeRange;
	Vector2 visibleSquirrelRange;

	float elapsedTimeSeconds;
public:
	std::vector<Squirrel> squirrelList;
	
	void resetVisibleRange();

	void generateGravel(std::vector<std::vector<Vector2>> rail, int concentration);
	void generateTrees(std::vector<Vector2> rail, int concentration, int offsetY, int scaleMin, int scaleMax);
	void generateSquirrels(std::vector<std::vector<Vector2>> rail, int concentration, int scaleMin, int scaleMax);

	void update();
	void draw();
	void drawUnderMountain();
};