#pragma once
#include "wheel.h"

class Stimulus : public Wheel {
public:
	Stimulus(float currentHeight)
		:Wheel(49, 70, 80, false, LIP_ROUND) {

		this->currentHeight = currentHeight;
		setColor(255, 95, 59);
	};
}