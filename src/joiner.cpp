#include "joiner.h"

void Joiner::initialize() {
	initialPosition = Vector2((SCREENWIDTH / 2) - (board.rectangle.width / 2), SCREENHEIGHT / 2);
	board.initialPosition = initialPosition;
	board.rectangle = VRectangle(initialPosition, 40, 10, 0);
	cameraPosition.x = initialPosition.x;

	world.generateTrack();
	world.generateSpeedZones();
}

void Joiner::update(int elapsedTime) {
	visibleFrame.position.x = cameraPosition.x - (SCREENWIDTH2 / 2);

	gui.updateSpeedometer((int)board.velocity, 2);
	gui.updateShoeometer((int)board.shoeLeft, 1);
	updateBoard(elapsedTime, speedZone);

	for (Vector2 speed : world.track.speedZones) {
		if (board.rectangle.position.x > world.track.railList[0][speed.x].x) {
			speedZone = speed.y;
		}
	}

	for (std::vector<Vector2> rail : world.track.railList) {
		for (int x = 0; x < rail.size(); x++) {
			if (board.rectangle.position.x + 100 > rail[x].x) {
				if (board.rectangle.position.x < rail[x].x + 100) {
					world.track.resetVisibleRange();
					handleCollision(rail[x], rail[x + 1]);
					handleCollision(rail[x], rail[x + 1]);
				}
			}
		}
	}
}

void Joiner::draw() {
	gui.draw();
	glTranslatef(-cameraPosition.x + initialPosition.x, -cameraPosition.y + initialPosition.y, 0);
	drawBoard();
	world.draw();
}