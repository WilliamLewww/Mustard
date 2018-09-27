#pragma once

enum {
	LIP_SQUARE = 1,
	LIP_ROUND = 2
};

class Wheel {
protected:
	float width, height;
	int durometer;
	int lipID;

	float currentHeightPercent;
	bool hasSkin;

	int color[3];

	inline void setColor(int r, int g, int b) {
		color[0] = r; color[1] = g; color[2] = b;
	};
public:
	inline Wheel() { };

	inline Wheel(float width, float height, int durometer, int lipID, bool hasSkin) {
		this->width = width;
		this->height = height;
		this->durometer = durometer;
		this->lipID = lipID;
		this->hasSkin = hasSkin;
	};

	inline float getWidth() { return width; };
	inline float getHeight() { return height; };
	inline float getCurrentHeightPercent() { return currentHeightPercent; };
	inline int getDurometer() { return durometer; };
	inline int getLipID() { return lipID; };
	inline bool getHasSkin() { return hasSkin; };

	inline void decayWheel(float angleDifference, float speed) {

	};

	// between 0 and 2 exclusive
	// 2 <-- more buttery
	// 0 <-- more grippy
	inline float getTraction() {
		float traction;
		return traction;
	};

	inline float getRollSpeed() {
		float speed;
		return speed;
	};
};

#include "wheel_butterballs.h"
#include "wheel_experimentals.h"
#include "wheel_snakes.h"
#include "wheel_stimulus.h"
#include "wheel_zigzags.h"

enum WHEEL {
	WHEEL_BUTTERBALLS = 1,
	WHEEL_EXPERIMENTALS = 2,
	WHEEL_SNAKES = 3,
	WHEEL_STIMULUS = 4,
	WHEEL_ZIGZAGS = 5
};

static std::string getWheelName(int wheelID) {
	std::string wheelNames[] = { "Butterballs", "Experimentals", "Snakes", "Stimulus", "ZigZags" };

	return wheelNames[wheelID - 1];
};