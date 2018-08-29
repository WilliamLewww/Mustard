#include "splits_display.h"

SplitsDisplay::SplitsDisplay(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;
}

void SplitsDisplay::draw() {
	drawing.drawRect(position, width, height, color);
}