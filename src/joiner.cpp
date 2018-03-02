#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	board.initialize();
	camera.linkPosition(board.bitmapPolygon.getPositionAddress());
	
	world.generateTrack();
	world.generateSpeedZones();
}

void Joiner::update(int elapsedTime) {
	board.update(elapsedTime, 10);
}

void Joiner::draw() {
	glPushMatrix();
	glTranslatef(-camera.getPosition().x + (configuration.getScreenWidth() / 2) - (board.bitmapPolygon.getWidth() / 2), -camera.getPosition().y + (configuration.getScreenHeight() / 2) - (board.bitmapPolygon.getHeight() / 2), 0);
	world.draw(1);
	board.draw();
	glPopMatrix();
}