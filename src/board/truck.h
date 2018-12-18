#pragma once
#include "..\core\timer.h"
#include "..\bmp_polygon.h"

class Truck {
private:
	int wheelColor[3];
	int truckColor[3] = { 51, 26, 0 };
	
	BitmapPolygon leftTruck, rightTruck;
	double* boardAngle;

	double additionalAngle = 0;
	bool turnLeft = false, turnRight = false;

	double turnRadius = 20;
	double carveStrength = 75, recovery = 150;
public:
	inline void setTurnLeft(bool turnLeft) { this->turnLeft = turnLeft; };
	inline void setTurnRight(bool turnRight) { this->turnRight = turnRight; };

	void setWheelColor(int r, int g, int b);
	void setWidth(int width);
	void setAngle(double* angle);
	void updatePosition(Vector2 left, Vector2 right);
	void draw(bool ridingSwitch);
};