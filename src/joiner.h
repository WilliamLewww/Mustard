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

	int speedZone = 0;

	int showBoardProperty;
	int trackGenerationStyle, boardID, boardWidth, boardHeight;
	float boardColor[4], thaneColor[3];
public:
	void initialize();
	void initializeWorld();
	void draw();
	void update(int elapsedTime);
};

extern Joiner joiner;