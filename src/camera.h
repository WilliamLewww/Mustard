#pragma once
#include "core\vector2.h"
#include "core\configuration.h"

class Camera {
private:
	Vector2* linkedPosition;
	int rangeWidth = 100, rangeHeight = 100;
public:
	inline Vector2 getPosition() { return *linkedPosition; }
	void linkPosition(Vector2* position);

	bool checkEntityInVisibleRange(Vector2 position, int width, int height);
	double getBoundaryLeft();
	double getBoundaryRight();
};

extern Camera camera;