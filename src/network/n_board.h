#pragma once
#include <string>
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class NBoard {
private:
	int ID;

	Vector2 position;
	int width, height;

	double angle;
public:
	NBoard(int ID);

	inline Vector2 getPosition() { return position; };

	inline int getWidth() { return width; };
	inline int getHeight() { return height; };
	inline double getAngle() { return angle; }

	void setFromString(std::string data);
	void draw();
};