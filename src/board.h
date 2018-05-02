#pragma once
#include <vector>
#include <string>
#include "camera.h"
#include "core\input.h"
#include "core\vector3.h"
#include "core\configuration.h"
#include "bmp_polygon.h"

class Board {
private:
	int thaneColor[3];

	float elapsedTimeSeconds;

	float velocity;
	int rollSpeed = 10;

	double pushInterval = 0.7, pushSpeed = 35, pushTimer = 0, pushMax = 150;
	double tuckSpeed = 8;
	double turnSpeed = 50;

	bool slide = false, shutdownSlide = false;
	bool turnLeft = false, turnRight = false;

	double movementAngle = 0;
	bool flipped = false;

	std::vector<Vector3> thaneLines;
	std::vector<Vector2> brakeLines;

	void addSpeedFromHill(int speedZone, int trackDirection);
	void handlePushTuck();
	void handleFootBrake();

	void handleLeftTurn();
	void handleRightTurn();

	double getAngleDifference();
	void handleSlideRight(double difference);
	void handleSlideLeft(double difference);

	Vector2 getDirection();
	void moveInDirection(Vector2 direction);

	void refreshSlide();

	void generateThane(int multiplier);
	void clearLines();
	void drawThaneLines();
	void drawBrakeLines();
	
	void linkPolygonWithConfigurations();
	void reset();
public:
	BitmapPolygon bitmapPolygon;
	
	void initialize();
	void update(int elapsedTimeSeconds, int speedZone, int trackDirection);
	void draw();

	void handleCollision(Vector2* wall);
	void handleCollision(Vector2 pointA, Vector2 pointB);
};