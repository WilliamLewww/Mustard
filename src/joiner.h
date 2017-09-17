#pragma once
#include "../constants.h"
#include "gui/gui.h"
#include "board.h"
#include "camera.h"
#include "environment.h"

class Joiner {
	World world;
	GUI gui;
	Vector2 startLine[2];
	int trackColor[3] = { 0, 0, 255 };

	Vector2 initialPosition;

	int speedZone = 0;

public:
	void initialize();
	void draw();
	void update(int elapsedTime);
};