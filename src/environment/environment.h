#pragma once
#include <vector>
#include <stdlib.h>
#include "..\core\timer.h"
#include "..\camera.h"
#include "tree.h"
#include "squirrel.h"

class Environment {
private:
	float elapsedTimeSeconds;

	Vector2 visibleTreeRange;
	std::vector<std::vector<Tree>> treeList;

	std::vector<Squirrel> squirrelList;
public:
	void resetVisibleRange();

	void generateTrees(std::vector<Vector2> rail, int concentration, int offsetY, int scaleMin, int scaleMax);
	void generateSquirrels(std::vector<Vector2> rail, int concentration, int scaleMin, int scaleMax);

	void update();
	void draw();
};