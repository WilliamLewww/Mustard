#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class GuardRail {
private:
	Vector2 segments[4];
	int color[3] = { 152, 166, 188 };
public:
	Vector2 nodeA, nodeB;

	GuardRail(Vector2 railNodeA, Vector2 railNodeB);
	void draw();
};