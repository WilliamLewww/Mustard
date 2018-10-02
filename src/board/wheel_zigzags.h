#pragma once
#include "wheel.h"

class ZigZags : public Wheel {
public:
	ZigZags(float currentHeightPercent)
		:Wheel(53, 70, 77, 95, LIP_SQUARE, true) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(56, 222, 64);
	};
};