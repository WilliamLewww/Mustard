#include "joiner.h"

void Joiner::initialize() {
	initialPosition = Vector2((SCREENWIDTH / 2) - (board.rectangle.width / 2), SCREENHEIGHT / 2);
	board.initialPosition = initialPosition;
	board.rectangle = VRectangle(initialPosition, 40, 10, 0);
	cameraPosition.x = initialPosition.x;

	std::vector<Vector2> tempTrack = generateTrackRand(2, 5, 20, Vector2((SCREENWIDTH / 2) - 30, (SCREENHEIGHT / 2) - 100));
	track.insert(track.end(), tempTrack.begin(), tempTrack.end());

	tempTrack = generateLongTrackRand(50, 100, 20, 20, track[track.size() - 1]);
	track.insert(track.end(), tempTrack.begin(), tempTrack.end());
	tempTrack = generateTrackComp(track, Vector2(track[0].x, track[0].y + 200), 200, -20, 20);
	trackCompliment.insert(trackCompliment.end(), tempTrack.begin(), tempTrack.end());

	startLine[0] = Vector2((SCREENWIDTH / 2) - 30, (SCREENHEIGHT / 2) - 100);
	startLine[1] = Vector2(track[0].x, track[0].y + 200);
}

void Joiner::update(int elapsedTime) {
	gui.updateSpeedometer((int)board.velocity, 1);
	updateBoard(elapsedTime);

	for (int x = 0; x < track.size(); x++) {
		if (board.rectangle.position.x + 100 > track[x].x) {
			if (board.rectangle.position.x < track[x].x + 100) {
				handleCollision(track[x], track[x + 1]);
				handleCollision(trackCompliment[x], trackCompliment[x + 1]);
			}
		}
	}
}

void Joiner::draw() {
	gui.draw();
	glTranslatef(-cameraPosition.x + initialPosition.x, -cameraPosition.y + initialPosition.y, 0);
	drawLine(startLine[0], startLine[1], trackColor);
	drawBoard();
	drawLineStrip(track, trackColor);
	drawLineStrip(trackCompliment, trackColor);
}