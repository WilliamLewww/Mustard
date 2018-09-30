#pragma once

enum {
	LIP_SQUARE = 1,
	LIP_ROUND = 2
};

class Wheel {
protected:
	int wheelID;

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

	inline int getID() { return wheelID; }
	inline void setID(int wheelID) { this->wheelID = wheelID; }

	inline float getWidth() { return width; };
	inline float getHeight() { return height; };
	inline float getCurrentHeightPercent() { return currentHeightPercent; };
	inline int getDurometer() { return durometer; };
	inline int getLipID() {  return lipID; };
	inline bool getHasSkin() { return hasSkin; };

	inline void decayWheel(float elapsedTimeSeconds, float angleDifference, float speed) {
		if (currentHeightPercent - (angleDifference * speed * 0.00001) * elapsedTimeSeconds < 0) {
			currentHeightPercent = 0.00;
		}
		else {
			currentHeightPercent -= (angleDifference * speed * 0.00001) * elapsedTimeSeconds;
		}

		if (currentHeightPercent < 0.98 && hasSkin == true) {
			hasSkin = false;
		}

		if (currentHeightPercent < 0.89 && lipID == LIP_SQUARE) {
			lipID = LIP_ROUND;
		}
	};

	// between 0 and 2 exclusive
	// 2 <-- more buttery
	// 0 <-- more grippy
	inline float getTraction() {
		float traction = 0.00;
		float multiplier = 2.00;
		traction += ((durometer - 70.0) / 20.0);
		traction += ((60.0 - width) / 60.0) * 0.55;
		traction += ((75.0 - (height * currentHeightPercent)) / 75.0) * 0.25;

		if (hasSkin == true) { multiplier -= 0.25; }
		if (lipID == LIP_SQUARE) { multiplier -= 0.12; }

		traction *= multiplier;

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

static std::string getWheelLipProfile(int lipID) {
	std::string lipProfile;
	switch (lipID) {
		case 1:
			lipProfile = "Square";
			break;
		case 2:
			lipProfile = "Round";
	}

	return lipProfile;
};

static std::string getWheelHasSkin(bool hasSkin) {
	std::string skin;
	switch (hasSkin) {
		case true:
			skin = "True";
			break;
		case false:
			skin = "False";
	}

	return skin;
}

static Wheel getWheel(int wheelID) {
	Wheel wheel;

	switch (wheelID) {
		case 1:
			wheel = Butterballs(1);
			break;
		case 2:
			wheel = Experimentals(1);
			break;
		case 3:
			wheel = Snakes(1);
			break;
		case 4:
			wheel = Stimulus(1);
			break;
		case 5:
			wheel = ZigZags(1);
			break;
	}

	return wheel;
};