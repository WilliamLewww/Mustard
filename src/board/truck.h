#pragma once
#include "..\core\timer.h"
#include "..\bmp_polygon.h"

class Truck {
private:
	int wheelColor[3];
	int truckColor[3] = { 166, 166, 166 };
	
	BitmapPolygon leftTruck, rightTruck;
	double* boardAngle;

	double additionalAngle = 0;
	bool turnLeft = false, turnRight = false;

	double carveStrength = 75, recovery = 125;
public:
	inline void setTurnLeft(bool turnLeft) { this->turnLeft = turnLeft; };
	inline void setTurnRight(bool turnRight) { this->turnRight = turnRight; };

	void setWidth(int width);
	void setAngle(double* angle);
	void updatePosition(Vector2 left, Vector2 right);
	void draw();
};