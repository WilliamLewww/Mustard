#pragma once
#include "vector2.h"
#include "geometry.h"
#include "input.h"
#include "camera.h"
#include <cmath>

struct Board {
	VRectangle rectangle;
	float velocity = 0;

	double pushInterval = 1.0;
	int turnSpeed = 75, pushSpeed = 50, breakSpeed = 100;
};
extern Board board;

void updateBoard(int elapsedTime);
void drawBoard();