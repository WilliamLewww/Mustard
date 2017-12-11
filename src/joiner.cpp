#include "joiner.h"

void Joiner::initialize() {
	initialPosition = Vector2((SCREENWIDTH / 2) - (board.rectangle.width / 2), SCREENHEIGHT / 2);
	linkBoard("board_1.txt", initialPosition, 40, 10);
	board.polylist.position = &board.rectangle.position;
	board.polylist.angle = &board.rectangle.angle;
	cameraPosition = &board.rectangle.position;

	world.generateTrack();
	world.generateSpeedZones();
}

void Joiner::update(int elapsedTime) {
	visibleFrame.position.x = cameraPosition->x - (SCREENWIDTH / 2);

	gui.updateSpeedometer((int)board.velocity, 2);
	gui.updateShoeometer((int)board.shoe.left, 1);
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
					world.reset();
					handleCollision(rail[x], rail[x + 1]);
					handleCollision(rail[x], rail[x + 1]);
				}
			}
		}
	}
}

void Joiner::draw() {
	glPushMatrix();
	glTranslatef(-cameraPosition->x + initialPosition.x, -cameraPosition->y + initialPosition.y, 0);
	world.draw();
	drawBoard();
	glPopMatrix();
	
	gui.draw();
}