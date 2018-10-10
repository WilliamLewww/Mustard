#pragma once
#include <vector>
#include <string>
#include "..\core\input.h"
#include "..\core\vector3.h"
#include "..\core\timer.h"
#include "..\core\configuration.h"
#include "..\effects\particle_manager.h"
#include "..\bmp_polygon.h"
#include "..\camera.h"
#include "profile.h"

class Board {
private:
	int thaneColor[3];

	float elapsedTimeSeconds;

	float velocity;
	int rollSpeed = 10;

	double pushInterval = 0.7, pushSpeed = 35, pushTimer = 0, pushMax = 150;
	double tuckSpeed = 8;

	double turnSpeed = 50;
	double additionalTurnSpeed = 10.0;

	bool forcedSlide = false;
	bool slide = false, shutdownSlide = false;
	bool turnLeft = false, turnRight = false;

	double movementAngle = 0;
	bool flipped = false;

	std::vector<Vector3> thaneLines;
	std::vector<Vector2> brakeLines;

	inline float getRollSpeed() { return rollSpeed * wheel->getRollSpeed(); };
	inline float getTurnSpeed() { return turnSpeed * wheel->getTraction(); };
	inline float getTurnRadius() { 
		float radius = (additionalTurnSpeed * deck->getTurnRadius()) - additionalTurnSpeed;
		if (radius > additionalTurnSpeed) { return turnSpeed + additionalTurnSpeed; }
		if (radius < -additionalTurnSpeed) { return turnSpeed - additionalTurnSpeed; }

		return turnSpeed + radius;
	};

	void initializeDeck();
	void initializeWheel();
	void linkPolygonWithConfigurations();

	void addSpeedFromHill(int speedZone, int trackDirection);
	void handlePushTuck();
	
	void handleLeftTurn();
	void handleRightTurn();

	double getAngleDifference();
	void handleSlideRight(double difference);
	void handleSlideLeft(double difference);

	Vector2 getDirection();
	void moveInDirection(Vector2 direction);

	void refreshSlide();

	void generateThane(int multiplier);
public:
	BitmapPolygon bitmapPolygon;
	Deck* deck;
	Wheel* wheel;

	inline void forceSlide() { forcedSlide = true; }
	inline float getVelocity() { return velocity; };
	
	void subtractSpeedExternal(float speed);
	
	void initialize();
	void update(int speedZone, int trackDirection);
	void reset();
	void draw();
	void drawThaneLines();

	void clearLines();

	bool handleCollision(Vector2 position, int width, int height);
	bool handleCollision(BitmapPolygon polygon);
	bool handleCollision(Vector2* wall);
	bool handleCollision(Vector2 pointA, Vector2 pointB);
};