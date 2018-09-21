#pragma once
#include <algorithm>
#include <vector>
#include "core\file.h"
#include "core\vector2.h"
#include "core\drawing.h"

class BitmapPolygon {
private:
	Vector2 position;
	double width, height;
	double angle;

	std::vector<Vector2> vertices;

	int color[3];
	int alpha;

	Vector2 project(Vector2 axisArgs, Vector2 vertex);
	double dotProduct(Vector2 projection, Vector2 axis);
	std::vector<double> getProducts(BitmapPolygon rectangle, Vector2 axis);
	std::vector<double> getProducts(Vector2* line, Vector2 axis);
public:
	inline float getX() { return position.x; };
	inline float getY() { return position.y; };

	inline void setX(float x) { this->position.x = x; };
	inline void setY(float y) { this->position.y = y; };

	inline void addX(float x) { this->position.x += x; };
	inline void addY(float y) { this->position.y += y; };

	inline void setPosition(Vector2 position) { this->position = position; };
	inline void setAngle(double angle) { this->angle = angle; };
	inline void addAngle(double angle) { this->angle += angle; };

	inline Vector2* getPositionAddress() { return &position; };
	inline Vector2 getPosition() { return position; };
	inline double getWidth() { return width; };
	inline double getHeight() { return height; };
	inline double getAngle() { return angle; };

	inline Vector2 getCenter() {
		return Vector2(position.x + (width / 2), position.y + (height / 2));
	};
	inline Vector2 getTopLeft() {
		return Vector2((-width / 2) * cos((angle * drawing.PI) / 180) - (height / 2) * sin((angle * drawing.PI) / 180) + position.x + (width / 2),
				   (width / 2) * sin((angle * drawing.PI) / 180) - (height / 2) * cos((angle * drawing.PI) / 180) + position.y + (height / 2));
	};
	inline Vector2 getTopRight() {
		return Vector2((width / 2) * cos((angle * drawing.PI) / 180) - (height / 2) * sin((angle * drawing.PI) / 180) + position.x + (width / 2),
				   (-width / 2) * sin((angle * drawing.PI) / 180) - (height / 2) * cos((angle * drawing.PI) / 180) + position.y + (height / 2));
	};
	inline Vector2 getBottomLeft() {
		return Vector2((-width / 2) * cos((angle * drawing.PI) / 180) - (-height / 2) * sin((angle * drawing.PI) / 180) + position.x + (width / 2),
				   (width / 2) * sin((angle * drawing.PI) / 180) - (-height / 2) * cos((angle * drawing.PI) / 180) + position.y + (height / 2));
	};
	inline Vector2 getBottomRight() {
		return Vector2((width / 2) * cos((angle * drawing.PI) / 180) - (-height / 2) * sin((angle * drawing.PI) / 180) + position.x + (width / 2),
				   (-width / 2) * sin((angle * drawing.PI) / 180) - (-height / 2) * cos((angle * drawing.PI) / 180) + position.y + (height / 2));
	};

	inline Vector2 axisA() { return getTopRight() - getTopLeft(); };
	inline Vector2 axisB() { return getTopRight() - getBottomRight(); };

	bool checkCollision(BitmapPolygon rectangle);
	bool checkCollision(Vector2* line);

	void setSize(int width, int height);
	void setColor(int red, int green, int blue, int alpha);
	void setVertices(const char* filename);

	void drawOutline();
};
