#pragma once
#include "wheel.h"

class ZigZags : public Wheel {
public:
	ZigZags(float currentHeightPercent)
		:Wheel(53, 70, 77, true, LIP_SQUARE) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(56, 222, 64);
	};
};