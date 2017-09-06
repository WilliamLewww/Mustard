#include "joiner.h"

void Joiner::initialize() {
	initialPosition = Vector2((SCREENWIDTH / 2) - (board.rectangle.width / 2), SCREENHEIGHT / 2);
	board.initialPosition = initialPosition;
	board.rectangle = VRectangle(initialPosition, 40, 10, 0);
	cameraPosition.x = initialPosition.x;

	world.generateTrack();
}

void Joiner::update(int elapsedTime) {
	gui.updateSpeedometer((int)board.velocity, 2);
	gui.updateShoeometer((int)board.shoeLeft, 1);
	updateBoard(elapsedTime);

	for (int x = 0; x < world.track.top.size(); x++) {
		if (board.rectangle.position.x + 100 > world.track.top[x].x) {
			if (board.rectangle.position.x < world.track.top[x].x + 100) {
				handleCollision(world.track.top[x], world.track.top[x + 1]);
				handleCollision(world.track.bottom[x], world.track.bottom[x + 1]);
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