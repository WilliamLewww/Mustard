#pragma once
#include "vector2.h"
#include "vector3.h"
#include "geometry.h"
#include "input.h"
#include "camera.h"
#include "polylist.h"
#include <cmath>

struct Board {
	VRectangle rectangle;
	Vector2 initialPosition;
	float velocity = 0;

	double pushInterval = 1.0;
	double recoverRate = 0.1;
	int turnSpeed = 75, pushSpeed = 50, breakSpeed = 100;
	int rollSpeed = 10, tuckSpeed = 15;
	int stability = 75;

	double shoeLeftInitial = 100;
	double shoeLeft = shoeLeftInitial;
	int shoeStrength = 7;

	int boardColor[3] = { 103, 156, 192 };
	int thaneColor[3] = { 255, 255, 255 };
	int breakColor[3] = { 0, 0, 0 };

	Polylist polylist;
};
extern Board board;

void linkBoard(const char* path, Vector2 initialPosition, double width, double height);
void updateBoard(int elapsedTime, int speedZone);
void drawBoard();

void handleCollision(Vector2* wall);
void handleCollision(Vector2 pointA, Vector2 pointB);