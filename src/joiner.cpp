#include "joiner.h"

void Joiner::initialize() {
	initialPosition = Vector2((SCREENWIDTH / 2) - (board.length / 2), SCREENHEIGHT / 2);
	board.position = initialPosition;

	std::vector<Vector2> tempTrack = generateTrackRand(2, 5, 20, Vector2((SCREENWIDTH / 2) - 30, (SCREENHEIGHT / 2) - 100));
	track.insert(track.end(), tempTrack.begin(), tempTrack.end());

	tempTrack = generateLongTrackRand(50, 100, 20, 20, track[track.size() - 1]);
	track.insert(track.end(), tempTrack.begin(), tempTrack.end());
	tempTrack = generateTrackComp(track, Vector2(track[0].x, track[0].y + 200), 200, -20, 20);
	trackCompliment.insert(trackCompliment.end(), tempTrack.begin(), tempTrack.end());
}

void Joiner::update(int elapsedTime) {
	updateBoard(elapsedTime);
}

void Joiner::draw() {
	glTranslatef(-cameraPosition.x + initialPosition.x, -cameraPosition.y + initialPosition.y, 0);
	drawBoard();
	drawLineStrip(track, trackColor);
	drawLineStrip(trackCompliment, trackColor);
}