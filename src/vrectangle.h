#pragma once
#include "../constants.h"
#include "vector2.h"
#include <vector>
#include <algorithm>  

class VRectangle {
public:
	Vector2 position;
	double width, height;
	double angle;

	VRectangle();
	VRectangle(Vector2 posArgs, double wArgs, double hArgs);
	VRectangle(Vector2 posArgs, double wArgs, double hArgs, double aArgs);

	inline Vector2 topLeft() {
		return Vector2((-width / 2) * cos((angle * pi) / 180) - (height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (width / 2) * sin((angle * pi) / 180) - (height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
	};
	inline Vector2 topRight() {
		return Vector2((width / 2) * cos((angle * pi) / 180) - (height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (-width / 2) * sin((angle * pi) / 180) - (height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
	};
	inline Vector2 bottomLeft() {
		return Vector2((-width / 2) * cos((angle * pi) / 180) - (-height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (width / 2) * sin((angle * pi) / 180) - (-height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
	};
	inline Vector2 bottomRight() {
		return Vector2((width / 2) * cos((angle * pi) / 180) - (-height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (-width / 2) * sin((angle * pi) / 180) - (-height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
	};

	inline Vector2 axisA() { return topRight() - topLeft(); };
	inline Vector2 axisB() { return topRight() - bottomRight(); };

	bool checkCollision(VRectangle rectangle);
	bool checkCollision(Vector2* line);
};

Vector2 project(Vector2 axisArgs, Vector2 vertex);
double dotProduct(Vector2 projection, Vector2 axis);
std::vector<double> getProducts(VRectangle rectangle, Vector2 axis);
std::vector<double> getProducts(Vector2* line, Vector2 axis);