#pragma once
#include "gui/gui.h"
#include "world.h"
#include "board.h"
#include "camera.h"
#include "configuration.h"

class Joiner {
private:
	World world;
	Board board;
	GUI gui;

	int speedZone = 0;
public:
	void initialize();
	void draw();
	void update(int elapsedTime);
};

extern Joiner joiner;