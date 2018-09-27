#pragma once
#include "wheel.h"

class Stimulus : public Wheel {
public:
	Stimulus(float currentHeightPercent)
		:Wheel(49, 70, 80, false, LIP_ROUND) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(255, 95, 59);
	};
};