#include "squirrel.h"

Squirrel::Squirrel(Vector2 position, Vector2 homePosition, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;

	this->homePosition = homePosition;
}

void Squirrel::update(float elapsedTimeSeconds) {
	if (position.x < homePosition.x) {
		position.x += 50 * elapsedTimeSeconds;
	}

	if (position.x > homePosition.x) {
		position.x -= 50 * elapsedTimeSeconds;
	}

	if (position.y < homePosition.y) {
		position.y += 50 * elapsedTimeSeconds;
	}

	if (position.y > homePosition.y) {
		position.y -= 50 * elapsedTimeSeconds;
	}
}

void Squirrel::draw() {
	drawing.drawRect(position, width, height);
}