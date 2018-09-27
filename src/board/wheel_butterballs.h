#pragma once
#include "wheel.h"

class Butterballs : public Wheel {
public:
	Butterballs(float currentHeightPercent)
		:Wheel(48, 70, 80, false, LIP_ROUND) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(255, 255, 255);
	};
};