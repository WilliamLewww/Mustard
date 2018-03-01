#pragma once
#include <fstream>
#include <vector>
#include "vector2.h"
#include "drawing.h"

class BitmapPolygon {
private:
	Vector2 position;
	double width, height;
	double angle;

	std::vector<Vector2> vertices;

	int color[3];
	int alpha;
public:
	inline void setPosition(Vector2 position) { this->position = position; };
	inline void setAngle(double angle) { this->angle = angle; };

	inline Vector2* getPositionAddress() { return &position; };
	inline Vector2 getPosition() { return position; };
	inline double getWidth() { return width; };
	inline double getHeight() { return height; };
	inline double getAngle() { return angle; };

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

	void setSize(int width, int height);
	void setColor(int red, int green, int blue, int alpha);
	void setVerticesFromFile(const char* filename);

	void drawOutline();
};
