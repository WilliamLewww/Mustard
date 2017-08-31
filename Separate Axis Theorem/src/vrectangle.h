#pragma once
#include "vector2.h"

class VRectangle {
public:
	Vector2 position;
	double width, height;
	double angle;

	VRectangle();
	VRectangle(Vector2 posArgs, double wArgs, double hArgs);
	VRectangle(Vector2 posArgs, double wArgs, double hArgs, double aArgs);

	double pi = 3.14159265359;

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

	inline Vector2 project(Vector2 axisArgs, Vector2 vertex) {
		return Vector2(
		(((vertex.x * axisArgs.x) + (vertex.y * axisArgs.y)) /
		(pow(axisArgs.x, 2) + pow(axisArgs.y, 2))) * axisArgs.x, 
		(((vertex.x * axisArgs.x) + (vertex.y * axisArgs.y)) /
		(pow(axisArgs.x, 2) + pow(axisArgs.y, 2))) * axisArgs.y);
	};

	inline double dotProduct(Vector2 projection, Vector2 axis) {
		return (projection.x * axis.x) + (projection.y * axis.y);
	};

	bool checkCollision(VRectangle rectangle);
};