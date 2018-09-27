#pragma once

enum {
	LIP_SQUARE = 1;
	LIP_ROUND = 2;
};

class Wheel {
protected:
	float width, height;
	int durometer;
	int lipID;

	float currentHeight;
	bool hasSkin;

	int color[3];

	inline void setColor(int r, int g, int b) {
		color[0] = r; color[1] = g; color[2] = b;
	};
public:
	inline Wheel(float width, float height, int durometer, int lipID, bool hasSkin) {
		this->width = width;
		this->height = height;
		this->durometer = durometer;
		this->lipID = lipID;
		this->hasSkin = hasSkin;
	};

	inline float getWidth() { return width; };
	inline float getHeight() { return height; };
	inline float getCurrentHeight() { return currentHeight; };
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
		return traction
	};

	inline float getRollSpeed() {
		float speed;
		return speed;
	};
}