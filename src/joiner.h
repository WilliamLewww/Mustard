#pragma once
#include "board.h"
#include "environment.h"

class Joiner {
	std::vector<Vector2> track;
	std::vector<Vector2> trackCompliment;
	int trackColor[3] = { 0, 0, 255 };

public:
	void initialize();
	void draw();
	void update(int elapsedTime);
};