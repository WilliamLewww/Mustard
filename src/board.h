#pragma once
#include "vector2.h"
#include "geometry.h"
#include "input.h"
#include "camera.h"
#include <cmath>

struct Board {
	VRectangle rectangle;
	Vector2 initialPosition;
	float velocity = 0;

	double pushInterval = 1.0;
	int turnSpeed = 75, pushSpeed = 50, breakSpeed = 100;
};
extern Board board;

void updateBoard(int elapsedTime);
void drawBoard();

void handleCollision(Vector2* wall);
void handleCollision(Vector2 pointA, Vector2 pointB);