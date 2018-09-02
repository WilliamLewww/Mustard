#pragma once
#include <ctime>
#include "core\configuration.h"
#include "core\gui.h"
#include "hud\hud.h"
#include "effects\particle_manager.h"
#include "world.h"
#include "board.h"
#include "camera.h"

class Joiner {
private:
	World world;
	Board board;
	HUD hud;

	int checkpointCount = 15;

	int speedZone = 0, trackDirection = 0;

	bool isPaused = false;
	bool showBuyMenu = true;
	bool showBoardEdit, showTrackEdit, showSessionStats = true, randomTrackSeed = false;

	int selectedRun = 0;
	int boardID, boardLength, boardWidth;
	int trackGenerationStyle;
	float boardColor[4], thaneColor[3];
public:
	int seed;

	void initialize();
	void initializeWorld();
	void draw();
	void update(int elapsedTime);
};

extern Joiner joiner;