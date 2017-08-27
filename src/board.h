#pragma once
#include "vector2.h"
#include "geometry.h"
#include "input.h"
#include <cmath>

struct Board {
	Vector2 position;
	float length = 40, width = 10;

	float velocity = 0;
	double rotation = 0;

	int turnSpeed = 75, slideSpeed = 50, pushSpeed = 75, breakSpeed = 100;

	inline Vector2 topLeft() { return Vector2(position.x + length, position.y); }
	inline Vector2 topRight() { return Vector2(position.x + length, position.y + width); }
	inline Vector2 bottomLeft() { return Vector2(position.x, position.y); }
	inline Vector2 bottomRight() { return Vector2(position.x, position.y + width); }
};
extern Board board;

void updateBoard(int elapsedTime);
void drawBoard();