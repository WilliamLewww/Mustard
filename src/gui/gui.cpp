#include "gui.h"

void GUI::draw() {
	minimap.draw();
}

void GUI::initializeMinimap(std::vector<std::vector<Vector2>> railList, Vector2 boardInitialPosition, Vector2 position, int width, int height) {
	minimap = Minimap(position, width, height);
	minimap.initialize(railList, boardInitialPosition);
}

void GUI::updateMinimap(Vector2 position, double angle) {
	minimap.update(position, angle);
}

void GUI::resetMinimap() {
	minimap.resetVisibleRange();
}