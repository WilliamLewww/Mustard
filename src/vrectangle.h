#pragma once
#include "vector2.h"
//#include "..\main.h"

class VRectangle {
public:
	Vector2 position;
	double width, height;
	double angle;

	VRectangle();
	VRectangle(Vector2 posArgs, double wArgs, double hArgs);
	VRectangle(Vector2 posArgs, double wArgs, double hArgs, double aArgs);

	Vector2 topLeft();
	Vector2 topRight();
	Vector2 bottomLeft();
	Vector2 bottomRight();
};