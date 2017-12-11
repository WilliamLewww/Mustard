#pragma once
#include "vector2.h"
#include "vector3.h"
#include "geometry.h"
#include "input.h"
#include "camera.h"
#include "polylist.h"
#include <cmath>

struct Wheel {
	int thaneColor[3] = { 255, 255, 255 };
};

struct Shoe {
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

	float velocity = 0;
	int boardColor[3] = { 103, 156, 192 };
};
extern Board board;

void linkBoard(const char* path, Vector2 initialPosition, double width, double height);
void updateBoard(int elapsedTime, int speedZone);
void drawBoard();

void handleCollision(Vector2* wall);
void handleCollision(Vector2 pointA, Vector2 pointB);