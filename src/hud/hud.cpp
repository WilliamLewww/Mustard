#include "hud.h"

void HUD::draw(bool showSplitsHUD, bool showKeyPressHUD, bool showMinimap) {
	if (showMinimap) { minimap.draw(); }
	if (showSplitsHUD) { splitsDisplay.draw(); }
	if (showKeyPressHUD) { keyDisplay.draw(); }
}

void HUD::initializeSplitsDisplay(int checkpointCount, Vector2 firstRail, Vector2 lastRail) {
	splitsDisplay.position = Vector2((configuration.getScreenWidth() / 2) - (splitsDisplay.width / 2), configuration.getScreenHeight() - splitsDisplay.height);
	splitsDisplay.generateCheckpoints(checkpointCount, firstRail, lastRail);
}

void HUD::updateSplitsDisplay(Vector2 bPosition) {
	splitsDisplay.update(bPosition);
}

void HUD::resetSplitsDisplay() {
	splitsDisplay.reset();
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