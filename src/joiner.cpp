#include "joiner.h"

void Joiner::initialize() {
	board.position = Vector2(50, 50);
}

void Joiner::update(int elapsedTime) {
	updateBoard(elapsedTime);
}

void Joiner::draw() {
	drawBoard();
}