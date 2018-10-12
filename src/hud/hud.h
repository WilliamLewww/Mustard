#pragma once
#include <vector>
#include "..\core\configuration.h"
#include "minimap.h"
#include "splits_display.h"
#include "key_display.h"

class HUD {
private:
	Minimap minimap = Minimap(Vector2(0, 0), 200, 200);
	KeyDisplay keyDisplay = KeyDisplay(Vector2(550, 500), 1);
public:
	SplitsDisplay splitsDisplay = SplitsDisplay(Vector2(0, 0), 500, 25);
	
	void initializeSplitsDisplay(int checkpointCount, Vector2 firstRail, Vector2 lastRail);
	void updateSplitsDisplay(Vector2 bPosition);
	void resetSplitsDisplay();
	void initializeMinimap(std::vector<std::vector<Vector2>> railList, Vector2 boardInitialPosition, Vector2 position, int width, int height);
	void updateMinimap(Vector2 position, double angle);
	void resetMinimap();
	void draw(bool showSplitsHUD, bool showKeyPressHUD, bool showMinimap);
};