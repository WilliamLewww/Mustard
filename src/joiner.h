#pragma once
#include "core\configuration.h"
#include "core\gui.h"
#include "hud\hud.h"
#include "world.h"
#include "board.h"
#include "camera.h"

class Joiner {
private:
	World world;
	Board board;
	HUD hud;

	int speedZone = 0, trackDirection = 0;

	bool showBuyMenu = true;
	bool showBoardEdit, showTrackEdit, showSessionStats = false, randomTrackSeed = true;

	int boardID, boardLength, boardWidth;
	int trackGenerationStyle, trackDifficulty, trackSeed;
	bool trackHard;
	float boardColor[4], thaneColor[3];
public:
	void initialize();
	void initializeWorld();
	void draw();
	void update(int elapsedTime);
};

extern Joiner joiner;