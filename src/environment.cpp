#include "environment.h"

void World::draw() {
	track.draw();
}

void World::generateTrack() {
	track.addVertex(Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2 - 20), 45);
	track.addVertexRelative(-50, 100, 150);
	track.addVertexRelative(0, 100, 150);
}