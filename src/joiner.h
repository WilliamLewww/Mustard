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
	
	bool showHUDEdit, showTrackEdit, showBoardEdit;
	bool showSplitsHUD = true, showKeyPressHUD = false, showMinimap = true;

	bool showInventory, showSessionStats = true, showLeaderboards = false, showWheelStats = true;
	bool randomTrackSeed = false;

	int selectedRun = 0, leaderboardSelectedRun = 0;
	int deckID, wheelID;
	int selectedDeck = 0, selectedWheel = 0;
	int trackGenerationStyle;

	void hideEditWindows();
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