#pragma once
#include "vector2.h"
#include "vector3.h"
#include "geometry.h"
#include "input.h"
#include "camera.h"
#include "polylist.h"
#include <cmath>

struct Wheel {
	int rollSpeed = 10;
	int thaneColor[3] = { 255, 255, 255 };
};

struct Shoe {
	double strength = 7;

	double initial = 100;
	double left = initial;
	int breakColor[3] = { 0, 0, 0 };
};

struct Board {
	Shoe shoe;
	Wheel wheel;

	Polylist polylist;
	VRectangle rectangle;
	Vector2 initialPosition;

	double pushInterval = 0.5, pushSpeed = 50, pushTimer = 0, pushMax = 150;
	
	double tuckSpeed = 8;
	double turnSpeed = 50;

	double slidePower = 0;

	float velocity = 0;
	int boardColor[3] = { 103, 156, 192 };
};
extern Board board;

void linkBoard(const char* path, Vector2 initialPosition, double width, double height);
void updateBoard(int elapsedTime, int speedZone);
void drawBoard();
void generateThane(int multiplier);

void handleCollision(Vector2* wall);
void handleCollision(Vector2 pointA, Vector2 pointB);