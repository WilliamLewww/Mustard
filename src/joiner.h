#pragma once
#include "hud/hud.h"
#include "world.h"
#include "board.h"
#include "camera.h"
#include "core\configuration.h"

class Joiner {
private:
	World world;
	Board board;
	HUD hud;

	int speedZone = 0;
public:
	void initialize();
	void draw();
	void update(int elapsedTime);
};

extern Joiner joiner;