#pragma once
#include "wheel.h"

class Snakes : public Wheel {
public:
	Snakes(float currentHeightPercent)
		:Wheel(48, 66, 83, 65, LIP_ROUND, false) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(255, 107, 95);
	};
};