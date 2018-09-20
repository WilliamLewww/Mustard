#include "guard_rail.h"

GuardRail::GuardRail(Vector2 railNodeA, Vector2 railNodeB) {
	nodeA = railNodeA;
	nodeB = railNodeB;

	segments[0] = Vector2(railNodeA.x, railNodeA.y);
	segments[1] = Vector2(railNodeA.x, railNodeA.y - 10);
	segments[2] = Vector2(railNodeB.x, railNodeB.y - 10);
	segments[3] = Vector2(railNodeB.x, railNodeB.y);
}

void GuardRail::draw() {
	drawing.drawLineStrip(segments, 4, Vector2(0, 0), 1, color);
}