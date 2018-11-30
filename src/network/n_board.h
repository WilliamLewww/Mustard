#pragma once
#include <queue>
#include <string>
#include "..\core\timer.h"
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class NBoard {
private:
	int ID;

	int width = 40, height = 10;

	Vector2 position;
	Vector2 positionSpeed;
	std::queue<Vector2> positionList;
	
	double angle;
	double angleSpeed = 0;
	std::queue<double> angleList;

	float startTime = 0, endTime = 0;
public:
	inline int getID() { return ID; };
	inline Vector2 getPosition() { return position; };
	inline double getAngle() { return angle; };
	inline int getWidth() { return width; };
	inline int getHeight() { return height; };

	NBoard(int ID);

	void addDataFromString(std::string data);

	void update();
	void draw();
};