#pragma once
#include "wheel.h"

class Snakes : public Wheel {
public:
	Snakes(float currentHeight)
		:Wheel(48, 66, 75, false, LIP_ROUND) {

		this->currentHeight = currentHeight;
		setColor(255, 107, 95);
	};

	inline float getTraction() {
		float traction;
		return traction
	};
}