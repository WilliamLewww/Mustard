#pragma once
#include <vector>
#include <string>
#include "core\input.h"
#include "core\vector3.h"
#include "core\timer.h"
#include "core\configuration.h"
#include "effects\particle_manager.h"
#include "bmp_polygon.h"
#include "camera.h"

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
	void drawBrakeLines();
	
	void linkPolygonWithConfigurations();
public:
	BitmapPolygon bitmapPolygon;

	inline float getVelocity() { return velocity; };
	
	void initialize();
	void update(int speedZone, int trackDirection);
	void reset();
	void draw();
	void drawThaneLines();

	void clearLines();

	bool handleCollision(BitmapPolygon polygon);
	bool handleCollision(Vector2* wall);
	bool handleCollision(Vector2 pointA, Vector2 pointB);
};