#pragma once
#include <ctime>
#include "core\configuration.h"
#include "core\gui.h"
#include "core\file.h"
#include "hud\hud.h"
#include "effects\particle_manager.h"
#include "environment\squirrel.h"
#include "board\board.h"
#include "world.h"
#include "camera.h"

class Joiner {
private:
	World world;
	Board board;
	HUD hud;

	int checkpointCount = 15;
	int tempHUDCheckpoint = 0;

	int speedZone = 0, trackDirection = 0;

	bool isPaused = false;
	bool isCrashed = false;
	bool allowRestartAfterCrash = false;
	bool isKeyStart = false;
	bool allowKeyStart = false;

	bool stillShowBoard = false;
	
	bool showBuyMenu = true;
	bool showBoardEdit, showTrackEdit, showSessionStats = true, showLeaderboards = false;
	bool randomTrackSeed = false;

	int selectedRun = 0, leaderboardSelectedRun = 0;
	int boardID, boardLength, boardWidth;
	int wheelID;
	int trackGenerationStyle;
	float thaneColor[3];
public:
	int seed;

	void reset(bool isCrash, bool crashedParticles);
	void resetFull();

	void initialize();
	void initializeWorld();
	void draw();
	void update();
};

extern Joiner joiner;