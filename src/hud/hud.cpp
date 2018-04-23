#include "hud.h"

void HUD::draw() {
	minimap.draw();
}

void HUD::initializeMinimap(std::vector<std::vector<Vector2>> railList, Vector2 boardInitialPosition, Vector2 position, int width, int height) {
	minimap = Minimap(position, width, height);
	minimap.initialize(railList, boardInitialPosition);
}

void HUD::updateMinimap(Vector2 position, double angle) {
	minimap.update(position, angle);
}

void HUD::resetMinimap() {
	minimap.resetVisibleRange();
}