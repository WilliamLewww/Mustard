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
	double recoverRate = 0.1;
	int turnSpeed = 75, pushSpeed = 50, breakSpeed = 100;
	int rollSpeed = 15, tuckSpeed = 15;

	double shoeLeftInitial = 100;
	double shoeLeft = shoeLeftInitial;
	int shoeStrength = 7;
};
extern Board board;

void updateBoard(int elapsedTime);
void drawBoard();

void handleCollision(Vector2* wall);
void handleCollision(Vector2 pointA, Vector2 pointB);