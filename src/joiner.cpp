#include "joiner.h"

void Joiner::initialize() {
	board.position = Vector2(25, 120);
	std::vector<Vector2> tempTrack = generateTrackRand(0, 5, 20, Vector2(0, 100));
	track.insert(track.end(), tempTrack.begin(), tempTrack.end());

	tempTrack = duplicateTrack(track, 50);
	trackCompliment.insert(trackCompliment.end(), tempTrack.begin(), tempTrack.end());

	tempTrack = generateTrackUp(10, 5, 25, Vector2(track[track.size() - 1].x, track[track.size() - 1].y));
	track.insert(track.end(), tempTrack.begin(), tempTrack.end());

	tempTrack = generateTrackDown(5, 5, 25, Vector2(trackCompliment[trackCompliment.size() - 1].x, trackCompliment[trackCompliment.size() - 1].y));
	trackCompliment.insert(trackCompliment.end(), tempTrack.begin(), tempTrack.end());
}

void Joiner::update(int elapsedTime) {
	updateBoard(elapsedTime);
}

void Joiner::draw() {
	drawBoard();
	drawLineStrip(track, trackColor);
	drawLineStrip(trackCompliment, trackColor);
}