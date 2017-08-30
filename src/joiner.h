#pragma once
#include "board.h"
#include "camera.h"
#include "environment.h"

class Joiner {
	Vector2 startLine[2];
	std::vector<Vector2> track;
	std::vector<Vector2> trackCompliment;
	int trackColor[3] = { 0, 0, 255 };

	Vector2 initialPosition;

public:
	void initialize();
	void draw();
	void update(int elapsedTime);
};